#include "iocontrollercommthread.h"

#include <QLoggingCategory>
Q_LOGGING_CATEGORY(DBG_IOCFLASH_COMMTREAD,"IOCFlash.CommThread", QtInfoMsg)

IoControllerCommThread::IoControllerCommThread()
{

    m_ReceiveStatus = eMessageSyncronizing;

    //Create a timer for controlling the communication state machine
    m_IOcontrTimer = new QTimer(this);
    connect(m_IOcontrTimer, SIGNAL(timeout()), this, SLOT(IOcontrCommProc()));
}

IoControllerCommThread::~IoControllerCommThread()
{
    //Cleanup
    delete(m_IOcontrTimer);
}

void IoControllerCommThread::run()
{

}

void IoControllerCommThread::IOcontrCommProc(void)
{
    //Timer event is used to control the get version progress. When a responce from the iocontroller is recieved, the
    //timer is set to fire immedeate. If no responce, the timer is preset to fire
    //in a sufficient amount of time, thus working as a timeout.

    m_IOcontrTimer->stop();

    if(m_ReceiveStatus != eMessageReceived && m_IOcontrStatus != eGetUserSWVer)
    {
        qCWarning(DBG_IOCFLASH_COMMTREAD) <<  "- Error! IOController did not respond";
        versionReport(m_SWversion);
    }
    else
    {
        switch(m_IOcontrStatus)
        {
            case eGetUserSWVer:
                m_IOcontrStatus = eAwaitUserSWver;
                sendReqUserSWver();
                m_IOcontrTimer->start(2000);
                break;
            case eAwaitUserSWver:
                versionReport(m_SWversion); //Timeout
                break;
            default:
                versionReport(m_SWversion);
                break;
        }
    }

}


void IoControllerCommThread::receivedData(void)
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
                //qDebug() << "eMessageSyncronizing: Recevied: " << data.at(dataIdx);
                dataIdx++;
            }
            if(dataIdx < data.size() && data.at(dataIdx) == '\0')
            {
                //qDebug()  << "eMessageSyncronizing: Frame start found. Clear recieve buffer";
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
                //qDebug() << "eMessageReceiving: Recevied: " << data.at(dataIdx);
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
                                qCWarning(DBG_IOCFLASH_COMMTREAD) << "IOCtrlCommController::receivedData - Error! Incorrect checksum";
                            }
                        }
                    }
                    else
                    {
                        qCWarning(DBG_IOCFLASH_COMMTREAD) << "Message decode failed";
                    }
                }
                else
                {
                    qCDebug(DBG_IOCFLASH_COMMTREAD) << "Getting next frame";
                }


                //Ready for next frame.
                //Note that end of this frame can also be start of next frame
                m_ReceiveStatus = eMessageSyncronizing;

            }
        }
    }
}

bool IoControllerCommThread::configureSerial(QString a_SerialPort, BaudRateType a_BaudRate)
{
    if (0 < a_SerialPort.length())
    {
        m_SerialPort = new QextSerialPort(a_SerialPort, QextSerialPort::EventDriven );
        m_SerialPort->setBaudRate(a_BaudRate);
        m_SerialPort->setFlowControl(FLOW_OFF);
        m_SerialPort->setParity(PAR_NONE);
        m_SerialPort->setDataBits(DATA_8);
        m_SerialPort->setStopBits(STOP_1);
        if(!m_SerialPort->open(QIODevice::ReadWrite))
        {
            qCWarning(DBG_IOCFLASH_COMMTREAD) <<  "Unable to open serial port : " << qPrintable(m_SerialPort->errorString());
            return false;
        }

        return true;
    }
    qCWarning(DBG_IOCFLASH_COMMTREAD) << "IoControllerCommThread::configureSerial() - No COM port defined";
    return false;
}

void IoControllerCommThread::versionReport(SWversion_t a_version)
{
    m_IOcontrTimer->stop();
    m_SerialPort->flush();
    m_SerialPort->close();

    disconnect(m_SerialPort, SIGNAL(readyRead()), this, SLOT(receivedData()));
    disconnect(m_IOcontrTimer, SIGNAL(timeout()), this, SLOT(IOcontrCommProc()));

    emit reportVersion(a_version);
}


void IoControllerCommThread::getVerIOprocessor(QString a_SerialPort)
{
    if(configureSerial(a_SerialPort, BAUD115200))
    {
        m_SerialPort->flush();

        connect(m_SerialPort, SIGNAL(readyRead()), this, SLOT(receivedData()));

        m_IOcontrStatus = eGetUserSWVer;

        m_IOcontrTimer->start(1);
    }
    else
    {
        //Report SW version 0
        emit reportVersion(m_SWversion);
    }
}

void IoControllerCommThread::parseMessage(const QVector<quint8> &a_Message)
{
    switch(a_Message[0])
    {
        case Communication::CommunicationIDs::RPL_USER_SW_VER:
        {
            m_SWversion.m_verMaj = a_Message[1];
            m_SWversion.m_verMin = a_Message[2];
            m_SWversion.m_verMaint = a_Message[3];
            m_SWversion.m_verBuild = a_Message[4];
            versionReport(m_SWversion);

            break;
        }
    }

    //exit(0);
}

void IoControllerCommThread::sendReqUserSWver(void)
{
    QByteArray buffer;
    encodeMessage(&buffer, Communication::CommunicationIDs::REQ_USER_SW_VER);
    if(m_SerialPort->write(buffer) != buffer.size())
    {
        qCWarning(DBG_IOCFLASH_COMMTREAD) << "Unable to write command REQ_USER_SW_VER";
    }
}


quint32 IoControllerCommThread::encodeMessage(QByteArray *a_buffer, quint8 a_messageId)
{

    QVector<quint8> message;
    message.reserve(MAX_MSGLEN_WITH_CRC);

    switch(a_messageId)
    {
        case Communication::CommunicationIDs::REQ_USER_SW_VER:
        {
            message.push_back(Communication::CommunicationIDs::REQ_USER_SW_VER);
            break;
        }

        default:
            break;
    }




    if (!message.empty() && MAX_MSGLEN >= message.size())
    {
        QVector<uint8_t> encodedBuffer(IoControllerCommThread::MAX_MSGLEN_OUTGOING + 2); // add space for framing
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
                a_buffer->append(byte);
            }

            return encodedBuffer.size();

        }

    }
    return 0;
}

bool IoControllerCommThread::cobsEncode(const QVector<quint8> &a_Source, QVector<quint8> &a_Destination)
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

bool IoControllerCommThread::cobsDecode(const QVector<quint8> &a_Source, QVector<quint8> &a_Destination)
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
