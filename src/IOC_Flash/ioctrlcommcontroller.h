#ifndef IOCTRL_COMM_CONTROLLER_H
#define IOCTRL_COMM_CONTROLLER_H

#include "iocontrollerupdatethread.h"
#include "iocontrollercommthread.h"
//#include <QVector>
#include <iostream>
//#include <QTimer>
//#include "Communication/CommunicationIDs.h"
//#include "Communication/CrcCCITT.h"
#include "SWversion.h"





class IOCtrlCommController : public QObject
{
    Q_OBJECT

    public:

        //! \brief IOCtrlCommController constructor
        //! \param a_Port - The COM port, I.E "COM1"
        //! \param a_filepathName - The path and filename of the sim file, I.E "IOProc\\IoController000100.sim"
        IOCtrlCommController(QString a_Port, QString a_filepathName, QString a_command);

        //! \brief IOCtrlCommController destructor
        ~IOCtrlCommController();


    private:
        //! \brief Copy constructor blocked
        IOCtrlCommController(const IOCtrlCommController &a_Right);

        //! \brief Assignment operator blocked
        IOCtrlCommController &operator=(const IOCtrlCommController &a_Right);

        //! \brief The thread used for updating IO controller (speak with bootloader)
        IoControllerUpdateThread *m_ioControllerUpdateThread;

        //! \brief The thread used for communication with IO controller (speak with user app)
        IoControllerCommThread *m_ioControllerCommThread;

        //! \brief Start update IO controller
        //! \param a_SimFileData - bytearray from a binary file read
        void updateIOprocessor(QByteArray a_SimFileData);

        //! \brief getSimFile - Read the update sim file from media
        //! \param a_filepathName - The path and filename of the sim file, I.E "IOProc\\IoController000100.sim"
        QByteArray getSimFile(QString a_filepathName);

        void getVersionIOprocessor(void);

        QString m_COMport;
        bool m_IOprocInUpdateMode;
        QString m_Filename;
        QString m_Command;


    private slots:
        void onInit();
        void onCommand(QString a_command);

    public slots:
        //! \brief Signal received from the update thread when update is finished
        //! \param a_result - True if succeeded update, false if failed
        void updateFinished(bool a_result);
        void reportVersion(SWversion_t a_version);


    signals:
        //! \brief Signal to thread for starting the update process
        //! \param pointer to the ready set-up serial port object
        //! \param bytearray from a binary file read
        void flashIOprocessor(QString a_SerialPort, QByteArray a_SimFileData);
        void getVerIOprocessor(QString a_SerialPort);

};

#endif // IOCtrlCommController_H
