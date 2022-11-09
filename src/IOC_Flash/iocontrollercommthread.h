#ifndef IOCONTROLLER_COMM_THREAD_H
#define IOCONTROLLER_COMM_THREAD_H

#include <qextserialport.h>
#include <QVector>
#include <QCoreApplication>
#include <QThread>
#include <QTimer>
#include "Communication/CommunicationIDs.h"
#include "Communication/CrcCCITT.h"
#include "SWversion.h"


class IoControllerCommThread : public QThread
{
    Q_OBJECT

    public:
        //! \brief ctor
        IoControllerCommThread();

        //! \brief dtor
        ~IoControllerCommThread();

        //! \brief The starting point for the thread
        void run();

        //! \brief The update state machine states
        enum Status_t {eGetUserSWVer, eAwaitUserSWver};


        //! \brief Receive status for the IO Controller communication
        enum ReceiveStatus_t {eMessageInit, eMessageSyncronizing, eMessageReceiving, eMessageError, eMessageReceived, eMessageTimeout};



    private:

        void versionReport(SWversion_t a_version);

        static const quint8 FRAMING_CHAR = 0;
        static bool cobsEncode(const QVector<quint8> &a_Source, QVector<quint8> &a_Destination);
        static bool cobsDecode(const QVector<quint8> &a_Source, QVector<quint8> &a_Destination);
        static const quint8 MAX_MSGLEN = 33;
        static const quint8 MAX_MSGLEN_WITH_CRC = (MAX_MSGLEN + Communication::CrcCCITT::CRC_LEN);
        static const quint8 COBS_OVERHEAD = 1; //COBS encoding
        static const quint8 MAX_MSGLEN_INCOMING = (MAX_MSGLEN_WITH_CRC + COBS_OVERHEAD);
        static const quint8 MAX_MSGLEN_OUTGOING = MAX_MSGLEN_INCOMING;


        void parseMessage(const QVector<quint8> &a_Message);
        quint32 encodeMessage(QByteArray *a_buffer, quint8 a_messageId);
        void sendReqUserSWver(void);
        bool configureSerial(QString a_SerialPort, BaudRateType a_BaudRate);

        //! \brief Serialport object used to communicate with IO Controller
        QextSerialPort *m_SerialPort;

        //! \brief Recieve status for the communication with IO Controller
        ReceiveStatus_t m_ReceiveStatus;

        //! \brief Timer used to control the state mashine for the update/get version process
        QTimer *m_IOcontrTimer;  //! \brief The state machine current state
        Status_t m_IOcontrStatus;

        QVector<quint8> m_ReceivedBuffer;

        SWversion_t m_SWversion;



    private slots:

        void IOcontrCommProc(void);

        void getVerIOprocessor(QString a_SerialPort);

        //! \brief Received data event from serial port object
        void receivedData(void);


    signals:
        void reportVersion(SWversion_t a_version);

};

#endif // IOCONTROLLER_COMM_THREAD_H
