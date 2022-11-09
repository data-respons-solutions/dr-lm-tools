#include "ioctrlcommcontroller.h"
#include <QLoggingCategory>
Q_LOGGING_CATEGORY(DBG_IOCFLASH_COMMCONTROLEER,"IOCFlash.CommController", QtInfoMsg)


IOCtrlCommController::IOCtrlCommController(QString a_Port, QString a_filepathName, QString a_command)
{
    m_COMport = a_Port;
    m_IOprocInUpdateMode = false;
    m_Filename = a_filepathName;
    m_Command = a_command;
    QTimer::singleShot(1, this, SLOT(onInit()));

}

IOCtrlCommController::~IOCtrlCommController()
{

}

void IOCtrlCommController::onInit()
{
    onCommand(m_Command);
}


void IOCtrlCommController::onCommand(QString a_command)
{
    if(a_command == "Update")
    {
        m_ioControllerUpdateThread = new IoControllerUpdateThread();
        connect(this, SIGNAL(flashIOprocessor(QString, QByteArray)), m_ioControllerUpdateThread, SLOT(updateIOcontroller(QString, QByteArray)));
        connect(m_ioControllerUpdateThread, SIGNAL(updateFinished(bool)), this, SLOT(updateFinished(bool)));
        m_ioControllerUpdateThread->start();

        QByteArray simFileData = getSimFile(m_Filename);
        updateIOprocessor(simFileData);
    }
    else if(a_command == "GetVersion")
    {
        m_ioControllerCommThread = new IoControllerCommThread();
        connect(this, SIGNAL(getVerIOprocessor(QString)), m_ioControllerCommThread, SLOT(getVerIOprocessor(QString)));
        connect(m_ioControllerCommThread, SIGNAL(reportVersion(SWversion_t)), this, SLOT(reportVersion(SWversion_t)));
        getVersionIOprocessor();
    }

    else
    {
        updateFinished(false);
    }
}

void IOCtrlCommController::updateIOprocessor(QByteArray a_SimFileData)
{

    if(m_IOprocInUpdateMode)
    {
        updateFinished(false); //If already updating
    }

    m_IOprocInUpdateMode = true;


    if(a_SimFileData.length() == 0)
    {
        qCWarning(DBG_IOCFLASH_COMMCONTROLEER, "No simfile found");
        updateFinished(false);
    }
    else
    {
        emit flashIOprocessor(m_COMport, a_SimFileData);
    }

}

void IOCtrlCommController::getVersionIOprocessor(void)
{
    emit getVerIOprocessor(m_COMport);
}

void IOCtrlCommController::updateFinished(bool a_result)
{
    m_ioControllerUpdateThread->wait();
    delete m_ioControllerUpdateThread;

    m_IOprocInUpdateMode = false;

    if(a_result)
    {
        qCInfo(DBG_IOCFLASH_COMMCONTROLEER, "Succeed");
        exit(0);
    }
    else
    {
        qCWarning(DBG_IOCFLASH_COMMCONTROLEER, "Fail to get IO Processor version!");
        exit(1);
    }

}

void IOCtrlCommController::reportVersion(SWversion_t a_version)
{
    m_ioControllerCommThread->wait();
    delete m_ioControllerCommThread;


    if(a_version.m_verMaj == 0 &&
       a_version.m_verMin == 0 &&
       a_version.m_verMaint == 0 &&
       a_version.m_verBuild == 0)
    {
        qCWarning(DBG_IOCFLASH_COMMCONTROLEER, "No version found");
        exit(1);
    }
    else
    {
        QString version;
        version.sprintf("%u.%u.%u.%u",
                        a_version.m_verMaj,
                        a_version.m_verMin,
                        a_version.m_verMaint,
                        a_version.m_verBuild);
        std::cout << std::endl << version.toStdString() << std::endl << std::flush;
        exit(0);
    }

}

QByteArray IOCtrlCommController::getSimFile(QString a_filepathName)
{
    QFile file(a_filepathName);

    qCInfo(DBG_IOCFLASH_COMMCONTROLEER, "Sim file: %s", qPrintable(file.fileName()));

    if(file.open(QFile::ReadOnly))
    {
        QByteArray fdata(file.readAll());
        file.close();
        return fdata;
    }

    QByteArray fdata("");
    return fdata;
}
