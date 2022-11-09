#include "ioctrlcommController.h"
#include "qextserialport.h"
// #include "logcontroller.h"
// #include "SessionStates.h"

IOCtrlCommController::IOCtrlCommController(// LM_VSCom::ParameterController *a_ParameterController, 
                                           QString a_Port, QObject *a_Parent)
    : QObject(a_Parent)
{
    m_ReceiveStatus = eMessageSyncronizing;
    m_COMport = a_Port;

    if (configureSerial(m_COMport, BAUD115200))
    {
        //        //Test

        //        ADCPollTimer = new QTimer(this);
        //        connect(ADCPollTimer, SIGNAL(timeout()), this, SLOT(ADCpoll()));
        //        ADCPollTimer->start(1000);
        //        sendReqUserSWver();

        //        sendTestModeCMD(0x01);              //Enter test mode

        //        sendTestSetIOCMD(0x01, 0x01);       //Set MCU_GPIO0 = HIGH
        //        sendTestSetIOCMD(0x02, 0x01);       //Set MCU_GPIO1 = HIGH
        //        sendTestSetIOCMD(0x03, 0x01);       //Set MCU_GPIO2 = HIGH
        //        sendTestSetIOCMD(0x04, 0x01);       //Set MCU_GPO1 = HIGH
        //        sendTestSetIOCMD(0x05, 0x01);       //Set MCU_GPO2 = HIGH
        //        sendTestSetIOCMD(0x01, 0x00);       //Set MCU_GPIO0 = LOW
        //        sendTestSetIOCMD(0x02, 0x00);       //Set MCU_GPIO1 = LOW
        //        sendTestSetIOCMD(0x03, 0x00);       //Set MCU_GPIO2 = LOW
        //        sendTestSetIOCMD(0x04, 0x00);       //Set MCU_GPO1 = LOW
        //        sendTestSetIOCMD(0x05, 0x00);       //Set MCU_GPO2 = LOW
        //        sendTestGetIOCMD(0x01);             //Read MCU_GPIO0
        //        sendTestGetIOCMD(0x01);             //Read MCU_GPIO0
        //        sendTestGetIOCMD(0x02);             //Read MCU_GPIO1
        //        sendTestGetIOCMD(0x02);             //Read MCU_GPIO1
        //        sendTestGetIOCMD(0x03);             //Read MCU_GPIO2
        //        sendTestGetIOCMD(0x03);             //Read MCU_GPIO2
        //        sendTestSetPwmCMD(0x00, 0x1000);    //Set Right carotid, 0x1000
        //        sendTestSetPwmCMD(0x00, 0x2000);    //Set Right carotid, 0x2000
        //        sendTestSetPwmCMD(0x00, 0x0000);    //Set Right carotid, 0x0000
        //        sendTestGetPulsePalpFreqCMD(0x00);  //Get Right carotid freq
        //        sendTestGetAdcCMD(12);              //Get ManikinID ADC value

        //        sendTestModeCMD(0x02);              //Exit test mode
    }
}


bool IOCtrlCommController::configureSerial(QString a_SerialPort, BaudRateType a_BaudRate)
{
    QString serialPort = a_SerialPort;
    if (0 == serialPort.length())
    {
        serialPort = "/dev/ttymxc3";
    }

    m_SerialPort = new QextSerialPort(serialPort, QextSerialPort::EventDriven );
    m_SerialPort->setBaudRate(a_BaudRate);
    m_SerialPort->setFlowControl(FLOW_OFF);
    m_SerialPort->setParity(PAR_NONE);
    m_SerialPort->setDataBits(DATA_8);
    m_SerialPort->setStopBits(STOP_1);
    m_SerialPort->open(QIODevice::ReadWrite);

    connect(m_SerialPort, SIGNAL(readyRead()), this, SLOT(receivedData()));

    return true;
}


void IOCtrlCommController::receivedData(void)
{
    QVector<quint8> decodedMessage;
    QByteArray data = m_SerialPort->readAll();
    qint32 dataIdx = 0;

    while(dataIdx < data.size())
    {
        if(m_ReceiveStatus == eMessageSyncronizing)
        {
            //First we have to look for frame start ('\0')
            while (dataIdx < data.size() && data.at(dataIdx) != '\0')
            {
                dataIdx++;
            }
            if(dataIdx < data.size() && data.at(dataIdx) == '\0')
            {
                //Frame start found. Clear recieve buffer
                dataIdx++;
                m_ReceivedBuffer.clear();
                m_ReceiveStatus = eMessageReceiving;
            }
        }

        if(m_ReceiveStatus == eMessageReceiving && dataIdx < data.size())
        {
            while (dataIdx < data.size() && data.at(dataIdx) != '\0')
            {
                //Add data to receive buffer until frame end, or end of received data from UART
                //If end of received data from UART before frame end, we will have to wait for next UART received data event
                m_ReceivedBuffer.push_back(data.at(dataIdx));
                dataIdx++;
            }

            if(dataIdx < data.size() && data.at(dataIdx) == '\0')
            {
                //Frame end found. Decode message
                if (m_ReceivedBuffer.size() > (COBS_OVERHEAD + Communication::CrcCCITT::CRC_LEN))
                {
                    decodedMessage.clear();
                    if (cobsDecode(m_ReceivedBuffer, decodedMessage))
                    {
                        if (decodedMessage.size() > Communication::CrcCCITT::CRC_LEN)
                        {
                            quint16 crc = decodedMessage.back();
                            crc <<= 8;
                            decodedMessage.pop_back();
                            crc |= decodedMessage.back();
                            decodedMessage.pop_back();

                            if (crc == Communication::CrcCCITT::calcCrc(&decodedMessage[0], static_cast<quint8>(decodedMessage.size())))
                            {
                                parseMessage(decodedMessage);
                            }
                            else
                            {
                                qDebug("IOCtrlCommController::receivedData() - Wrong checksum");
                            }
                        }
                    }
                }

                //Ready for next frame.
                //Note that end of this frame can also be start of next frame
                m_ReceiveStatus = eMessageSyncronizing;
            }
        }
    }
}

void IOCtrlCommController::parseMessage(const QVector<quint8> &a_Message)
{
    switch(a_Message[0])
    {
    case Communication::CommunicationIDs::RPL_USER_SW_VER:
    {
        m_IOprocUserSWver.m_verMaj = a_Message[1];
        m_IOprocUserSWver.m_verMin = a_Message[2];
        m_IOprocUserSWver.m_verMaint = a_Message[3];
        m_IOprocUserSWver.m_verBuild = a_Message[4];
        qDebug("IOCtrlCommController::parseMessage() RPL_USER_SW_VER - %u.%u.%u.%u",
               m_IOprocUserSWver.m_verMaj,
               m_IOprocUserSWver.m_verMin,
               m_IOprocUserSWver.m_verMaint,
               m_IOprocUserSWver.m_verBuild);
        break;
    }
    case Communication::CommunicationIDs::RPL_MANIKINTYPE:
    {
        qDebug("IOCtrlCommController::parseMessage() - RPL_MANIKINTYPE = %u", a_Message[1]);
        // m_LOCALAnalogManikinType->setValue(a_Message[1]);
        break;
    }
    case Communication::CommunicationIDs::RPL_TEST_GET_IO:
    {
        // qDebug("IOCtrlCommController::parseMessage() RPL_TEST_GET_IO - Ch:%u Val:%x",
        //        a_Message[1], a_Message[2]);
        emit gpioMessage(a_Message[1], a_Message[2]);
        break;
    }
    case Communication::CommunicationIDs::RPL_TEST_GET_PULSE_PALP_FREQ:
    {
        quint32 freq = (quint32)a_Message[2];
        freq |= (quint32)a_Message[3] << 8;
        freq |= (quint32)a_Message[4] << 16;
        freq |= (quint32)a_Message[5] << 24;
        // qDebug("IOCtrlCommController::parseMessage() RPL_TEST_GET_PULSE_PALP_FREQ - Ch:%u Val:%u",
        //        a_Message[1], freq);
        emit pulseMessage(a_Message[1], freq);
        break;
    }
    case Communication::CommunicationIDs::RPL_TEST_GET_AD:
    {
        quint16 val = (quint16)a_Message[2];
        val |= (quint16)a_Message[3] << 8;
        // qDebug("IOCtrlCommController::parseMessage() RPL_TEST_GET_AD - Ch:%u Val:%u",
        //        a_Message[1], val);
        emit adcMessage(a_Message[1], val);
        break;
    }
    case Communication::CommunicationIDs::CMD_EVENT_BP_CUFF_VALUE:
    {
        quint16 cuffp = (quint32)a_Message[1];
        cuffp |= (quint32)a_Message[2] << 8;

        emit cuffMessage(cuffp);
        // m_BPCuffPressure->setValue(cuffp);
        // qDebug("IOCtrlCommController::parseMessage() CMD_EVENT_BP_CUFF_VALUE - %u", (quint16)cuffp);
        break;
    }
    default:
    	break;
    }
}

void IOCtrlCommController::sendReqUserSWver(void)
{
    QMutexLocker lock(&m_sendMutex);

    QByteArray buffer;
    encodeMessage(&buffer, Communication::CommunicationIDs::REQ_USER_SW_VER);
    m_SerialPort->write(buffer);
}

void IOCtrlCommController::sendTestModeCMD(quint8 a_cmdType)
{
    QMutexLocker lock(&m_sendMutex);

    QByteArray buffer;
    encodeMessage(&buffer, Communication::CommunicationIDs::CMD_TEST_MODE, a_cmdType);
    m_SerialPort->write(buffer);
}

void IOCtrlCommController::sendTestSetIOCMD(quint16 a_channel, quint16 a_val)
{
    QMutexLocker lock(&m_sendMutex);

    QByteArray buffer;
    encodeMessage(&buffer, Communication::CommunicationIDs::CMD_TEST_SET_IO, a_channel, a_val);
    m_SerialPort->write(buffer);
}

void IOCtrlCommController::sendTestGetIOCMD(quint16 a_channel)
{
    QMutexLocker lock(&m_sendMutex);

    QByteArray buffer;
    encodeMessage(&buffer, Communication::CommunicationIDs::CMD_TEST_GET_IO, a_channel);
    m_SerialPort->write(buffer);
}

void IOCtrlCommController::sendTestSetPwmCMD(quint16 a_channel, quint16 a_val)
{
    QMutexLocker lock(&m_sendMutex);

    QByteArray buffer;
    encodeMessage(&buffer, Communication::CommunicationIDs::CMD_TEST_SET_PWM, a_channel, a_val);
    m_SerialPort->write(buffer);
}

void IOCtrlCommController::sendTestGetPulsePalpFreqCMD(quint16 a_channel)
{
    QMutexLocker lock(&m_sendMutex);

    QByteArray buffer;
    encodeMessage(&buffer, Communication::CommunicationIDs::CMD_TEST_GET_PULSE_PALP_FREQ, a_channel);
    m_SerialPort->write(buffer);
}

void IOCtrlCommController::sendTestGetAdcCMD(quint16 a_channel)
{
    QMutexLocker lock(&m_sendMutex);

    QByteArray buffer;
    encodeMessage(&buffer, Communication::CommunicationIDs::CMD_TEST_GET_AD, a_channel);
    m_SerialPort->write(buffer);
}

quint32 IOCtrlCommController::encodeMessage(QByteArray *a_buffer, quint8 a_messageId)
{
    return encodeMessage(a_buffer, a_messageId, 0, 0);
}

quint32 IOCtrlCommController::encodeMessage(QByteArray *a_buffer, quint8 a_messageId, quint16 a_data_1)
{
    return encodeMessage(a_buffer, a_messageId, a_data_1, 0);
}

quint32 IOCtrlCommController::encodeMessage(QByteArray *a_buffer, quint8 a_messageId, quint16 a_data_1, quint16 a_data_2)
{

    QVector<quint8> message;
    message.reserve(MAX_MSGLEN_WITH_CRC);

    switch(a_messageId)
    {
        case Communication::CommunicationIDs::REQ_MANIKINTYPE:
        {
            message.push_back(Communication::CommunicationIDs::REQ_MANIKINTYPE);
            break;
        }
        case Communication::CommunicationIDs::REQ_USER_SW_VER:
        {
            message.push_back(Communication::CommunicationIDs::REQ_USER_SW_VER);
            break;
        }
        case Communication::CommunicationIDs::CMD_SET_AIRWAY:
        {
            message.push_back(Communication::CommunicationIDs::CMD_SET_AIRWAY);
            message.push_back(a_data_1 & 0x00ff);
            break;
        }
        case Communication::CommunicationIDs::CMD_SET_CHEST_RISE:
        {
            message.push_back(Communication::CommunicationIDs::CMD_SET_CHEST_RISE);
            message.push_back(a_data_1 & 0x00ff);
            break;
        }
        case Communication::CommunicationIDs::CMD_SET_POWER_PANEL:
        {
            message.push_back(Communication::CommunicationIDs::CMD_SET_POWER_PANEL);
            message.push_back(a_data_1 & 0x00ff);
            message.push_back(a_data_2 & 0x00ff);
            message.push_back((a_data_2 & 0xff00) >> 8);
            break;
        }
        case Communication::CommunicationIDs::REQ_NECK_TILT:
        {
            message.push_back(Communication::CommunicationIDs::REQ_NECK_TILT);
            break;
        }
        case Communication::CommunicationIDs::CMD_TEST_MODE:
        {
            message.push_back(Communication::CommunicationIDs::CMD_TEST_MODE);
            message.push_back(a_data_1 & 0x00ff);
            break;
        }
        case Communication::CommunicationIDs::CMD_TEST_SET_IO:
        {
            message.push_back(Communication::CommunicationIDs::CMD_TEST_SET_IO);
            message.push_back(a_data_1 & 0x00ff);
            message.push_back(a_data_2 & 0x00ff);
            break;
        }
        case Communication::CommunicationIDs::CMD_TEST_GET_IO:
        {
            message.push_back(Communication::CommunicationIDs::CMD_TEST_GET_IO);
            message.push_back(a_data_1 & 0x00ff);
            break;
        }
        case Communication::CommunicationIDs::CMD_TEST_SET_PWM:
        {
            message.push_back(Communication::CommunicationIDs::CMD_TEST_SET_PWM);
            message.push_back(a_data_1 & 0x00ff);
            message.push_back(a_data_2 & 0x00ff);
            message.push_back((a_data_2 & 0xff00) >> 8);
            break;
        }
        case Communication::CommunicationIDs::CMD_TEST_GET_PULSE_PALP_FREQ:
        {
            message.push_back(Communication::CommunicationIDs::CMD_TEST_GET_PULSE_PALP_FREQ);
            message.push_back(a_data_1 & 0x00ff);
            break;
        }
        case Communication::CommunicationIDs::CMD_TEST_GET_AD:
        {
            message.push_back(Communication::CommunicationIDs::CMD_TEST_GET_AD);
            message.push_back(a_data_1 & 0x00ff);
            break;
        }

        default:
            break;
    }

    if (!message.empty() && MAX_MSGLEN >= message.size())
    {
        QVector<uint8_t> encodedBuffer(IOCtrlCommController::MAX_MSGLEN_OUTGOING + 2); // add space for framing
        quint16 crc = Communication::CrcCCITT::calcCrc(&message[0], static_cast<quint8>(message.size()));
        message.push_back(crc & 0x00ffu);
        message.push_back((crc & 0xff00u) >> 8);

        encodedBuffer.resize(0);
        encodedBuffer.push_back(0); //FRAMING_CHAR

        if (cobsEncode( message, encodedBuffer))
        {
            encodedBuffer.push_back(0);
            Q_FOREACH(quint8 byte, encodedBuffer)
            {
                *a_buffer->append(byte);
            }

            return encodedBuffer.size();
        }
    }
    return 0;
}

bool IOCtrlCommController::cobsEncode(const QVector<quint8> &a_Source, QVector<quint8> &a_Destination)
{
    if (!a_Source.empty() && !a_Destination.empty())
    {
        uint8_t code = 0x01;
        a_Destination.push_back(code); // make space for the first COBS code
        int codeIndex = a_Destination.size() - 1;

        for (int i = 0; i < a_Source.size(); i++)
        {
            if (0 == a_Source[i])
            {
                // Insert COBS code
                a_Destination[codeIndex] = code;
                code = 0x01;
                a_Destination.push_back(code); // make space for the next COBS code
                codeIndex = a_Destination.size() - 1;
            }
            else
            {
                a_Destination.push_back(a_Source[i]);
                code++;
                if (0xFF==code)
                {
                    // Insert COBS code
                    a_Destination[codeIndex] = code;
                    code = 0x01;
                    a_Destination.push_back(code); // make space for the next COBS code
                    codeIndex = a_Destination.size() - 1;
                }
            }
        }

        // Insert final COBS code
        a_Destination[codeIndex] = code;

        return true;
    }
    return false;
}

bool IOCtrlCommController::cobsDecode(const QVector<quint8> &a_Source, QVector<quint8> &a_Destination)
{
        if (a_Source.size() > COBS_OVERHEAD)
        {
            int index = 0;
            while (index < a_Source.size())
            {
                uint8_t code = a_Source[index++];
                for (uint8_t i = 1; i < code; i++)
                {
                    if (index < a_Source.size())
                        a_Destination.push_back(a_Source[index++]);
                }
                if (code < 0xFF)
                {
                    if (index < a_Source.size()) // we do not need the phantom zero
                        a_Destination.push_back(0);
                }
            }
            return true;
        }
        return false;
}

void IOCtrlCommController::sendEventGetManikinType(void)
{
    QMutexLocker lock(&m_sendMutex);

    QByteArray buffer;
    encodeMessage(&buffer, Communication::CommunicationIDs::REQ_MANIKINTYPE);
    m_SerialPort->write(buffer);
}

void IOCtrlCommController::sendBloodPressure(void)
{
    QMutexLocker lock(&m_sendMutex);

    QByteArray buffer;
    encodeMessage(&buffer, Communication::CommunicationIDs::CMD_SET_BP);
    m_SerialPort->write(buffer);
}
