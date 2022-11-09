#include "pso.hpp"

#include <QStringList>

PSO::PSO(int &argc, char *argv[])
    : QCoreApplication(argc, argv)
    , m_returnCode(0)
    , m_ioc(0)
    , m_count(0)
    , m_maxCount(10)
    , m_delay(1000)
    , m_readChannel(1)
{
    m_ioc = new IOCtrlCommController("/dev/ttymxc3");
    m_ioc->sendTestModeCMD(0x01); // on

    QString arg;
    Q_FOREACH(arg, arguments())
    {
        if (arg.startsWith("--channel="))
        {
            bool ok;
            quint16 v = arg.mid(10).toUInt(&ok, 10);
            if (ok)
                m_readChannel = v;
        }
        else if (arg.startsWith("--count="))
        {
            bool ok;
            quint16 v = arg.mid(8).toUInt(&ok, 10);
            if (ok)
                m_maxCount = v;
        }
        else if (arg.startsWith("--delay="))
        {
            bool ok;
            quint16 v = arg.mid(8).toUInt(&ok, 10);
            if (ok)
                m_delay = v;
        }
    }
    qDebug().nospace() << "Options: channel=" << m_readChannel
                       << ", count=" << m_maxCount
                       << ", delay=" << m_delay;

    connect(this, SIGNAL(go()),
            this, SLOT(goImpl()),
            Qt::QueuedConnection);
    emit go();
}

PSO::~PSO()
{
    m_ioc->sendTestModeCMD(0x02);
    delete m_ioc;
}

void PSO::goImpl()
{
    connect(this, SIGNAL(getValue()),
            this, SLOT(getValueImpl()),
            Qt::AutoConnection);
    connect(m_ioc, SIGNAL(pulseMessage(quint16, quint32)),
            this, SLOT(newPsoValue(quint16, quint32)),
            Qt::QueuedConnection);
    m_ioc->sendTestSetIOCMD(3, 0x01);
    emit getValue();
}

void PSO::setReturnCode(int code)
{
    m_returnCode = code;
}

void PSO::getValueImpl()
{
    m_count++;
    if (m_count > m_maxCount)
    {
        quitApplication();
    }
    m_ioc->sendTestGetPulsePalpFreqCMD(m_readChannel-1);
}

void PSO::quitApplication()
{
    exit(m_returnCode);
}

void PSO::newPsoValue(quint16 channel, quint32 value)
{
    qDebug() << "PSO channel" << channel+1
             << "value" << value;
    QTimer::singleShot(m_delay, this, SLOT(getValueImpl()));
}
