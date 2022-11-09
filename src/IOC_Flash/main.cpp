//#include "systemApi/deviceconfiguration.h"
//#include "AppConfig.h"
#include "ioctrlcommcontroller.h"

#include <QCoreApplication>
#include <QSettings>
#include <QJsonValue>
#include <iostream>
#include <cstdlib>
#if 0
#ifdef Q_OS_LINUX
extern "C" {
#include <signal.h>
void signal_handler(__attribute__((unused)) int a_signal)
{
    qDebug("Signal %d received!",a_signal);
    qApp->exit(1);
}
}
#endif
#endif
int main(int argc, char *argv[])
{
#if 0
#ifdef Q_OS_LINUX
    // Register signal handler
    signal(SIGINT, &signal_handler);   // Ctrl-C
    signal(SIGTERM, &signal_handler);  // kill
#endif
#endif
    QCoreApplication a(argc, argv);

    /*if(AppConfig::instance().initialize("Link Box IO Controller Flasher") == AppConfig::initExit_t)
    {
        return 0;
    }
    qSetMessagePattern("%{if-warning}Warning | %{endif}%{if-critical}Critical | %{endif}%{if-fatal}Fatal | %{endif}%{category} | %{message}");
*/

    QString commPort ="/dev/ttymxc3";

    QStringList cmdLineArgs = a.arguments();
    QString fn;
    QString cmd;
    IOCtrlCommController *ioCtrlCommController;

    if(cmdLineArgs.size() > 1)
    {
        for(qint32 i = 1; i < cmdLineArgs.size(); i++)
        {
            if(cmdLineArgs.at(i) == "--get-version")
            {
                cmd = "GetVersion";
            }
            else if(cmdLineArgs.at(i).startsWith("--file-name="))
            {
                fn = cmdLineArgs.at(i).toLatin1();
                fn.remove(0,12); //Remove --file-name=
                cmd = "Update";
            }
            else if(cmdLineArgs.at(i).startsWith("--com-port="))
            {
                commPort = cmdLineArgs.at(i).toLatin1();
                commPort.remove(0,11); //Remove --com-port=
            }
            else if(cmdLineArgs.at(i).size() > 0 && !cmdLineArgs.at(i).startsWith("--"))
            {
                //Assume this is file name
                fn = cmdLineArgs.at(i).toLatin1();
                cmd = "Update";
            }
        }
    }

    if(cmd.length() == 0)
    {
        std::cout << "Usage: " << argv[0] << " file name" << std::endl 
                  << " or " << argv[0] << " --get-version" << std::endl
                  << " or " << argv[0] << " --com-port=DEVICE_FILE --file-name=FILE_NAME" << std::endl << std::flush;
        return EXIT_FAILURE;
    }
    else
    {
        ioCtrlCommController = new IOCtrlCommController(commPort, fn, cmd);
        //IOCtrlCommController IOCtrlCommController(commPort, fn, cmd);
    }

    int ret = a.exec();
    delete ioCtrlCommController;
    return ret;
}
