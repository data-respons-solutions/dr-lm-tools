#ifndef IOCTRL_COMM_CONTROLLER_H
#define IOCTRL_COMM_CONTROLLER_H

#include "SWversion.h"
#include "Communication/CommunicationIDs.h"
#include "Communication/CrcCCITT.h"
#include "SWversion.h"
#include <qextserialport.h>
#include <QMutex>
#include <QVector>
#include <QTimerEvent>
#include <QDebug>

class IOCtrlCommController : public QObject
{
    Q_OBJECT

public:
    IOCtrlCommController(QString a_Port, QObject *a_Parent = 0);

    static const uint8_t MAX_MSGLEN = 33;
    static const uint8_t MAX_MSGLEN_WITH_CRC = (MAX_MSGLEN + Communication::CrcCCITT::CRC_LEN);
    static const uint8_t COBS_OVERHEAD = 1; //COBS encoding
    static const uint8_t MAX_MSGLEN_INCOMING = (MAX_MSGLEN_WITH_CRC + COBS_OVERHEAD);
    static const uint8_t MAX_MSGLEN_OUTGOING = MAX_MSGLEN_INCOMING;
    enum ReceiveStatus_t {eMessageInit, eMessageSyncronizing, eMessageReceiving, eMessageError, eMessageReceived, eMessageTimeout};

private:
    //! \brief Copy constructor blocked
    IOCtrlCommController(const IOCtrlCommController &a_Right);

    //! \brief Assignment operator blocked
    IOCtrlCommController &operator=(const IOCtrlCommController &a_Right);

    static bool cobsEncode(const QVector<quint8> &a_Source, QVector<quint8> &a_Destination);
    static bool cobsDecode(const QVector<quint8> &a_Source, QVector<quint8> &a_Destination);

    bool configureSerial(QString a_SerialPort, BaudRateType a_BaudRate);
    void parseMessage(const QVector<quint8> &a_Message);
    quint32 encodeMessage(QByteArray *a_buffer, quint8 a_messageId);
    quint32 encodeMessage(QByteArray *a_buffer, quint8 a_messageId, quint16 a_data_1);
    quint32 encodeMessage(QByteArray *a_buffer, quint8 a_messageId, quint16 a_data_1, quint16 a_data_2);

    QextSerialPort *m_SerialPort;
    QString m_COMport;
    ReceiveStatus_t m_ReceiveStatus;
    QVector<quint8> m_ReceivedBuffer;
    SWversion_t m_IOprocUserSWver;
    QMutex m_sendMutex;

public slots:
    void sendReqUserSWver(void);

    void sendTestModeCMD(quint8 a_cmdType);
    void sendTestSetIOCMD(quint16 a_channel, quint16 a_val);
    void sendTestGetIOCMD(quint16 a_channel);
    void sendTestSetPwmCMD(quint16 a_channel, quint16 a_val);
    void sendTestGetPulsePalpFreqCMD(quint16 a_channel);
    void sendTestGetAdcCMD(quint16 a_channel);

    void sendBloodPressure(void);
    void sendEventGetManikinType(void);

private slots:
    void receivedData(void);

signals:
    void adcMessage(quint16 channel, quint16 value);
    void gpioMessage(quint16 channel, quint16 value);
    void pulseMessage(quint16 channel, quint32 frequency);
    void versionMessage(quint32 major, quint32 minor);
    void cuffMessage(quint32 value);
};

#endif // IOCtrlCommController_H
