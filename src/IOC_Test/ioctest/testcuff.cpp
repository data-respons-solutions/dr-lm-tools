#include "testcuff.h"

// #include "testmodewrapper.h"

TestCuff::TestCuff(IOCtrlCommController * controller,
                   quint32 threshold,
                   QObject *parent)
    : QObject(parent)
    , m_controller(controller)
    , m_reporter(0)
    , m_channel(0)
    , m_maxReceived(0)
    , m_threshold(threshold)
    , m_semaphore(0)
{ }

QString TestCuff::getName() const
{
    return QString("Cuff");
}

void TestCuff::setReporter(ITestReporter *reporter)
{
    m_reporter = reporter;
}

void TestCuff::receivedMessage(quint32 value)
{
    qDebug() << "TestCuff::receivedMessage() value:" << value;
    if (value >= m_threshold)
    {
        m_maxReceived = std::max<quint32>(value, m_maxReceived);
        m_semaphore.release();
    }
}

void TestCuff::runTest()
{
    // TestModeWrapper testmode(m_controller);

    connect(m_controller, SIGNAL(cuffMessage(quint32)),
            this, SLOT(receivedMessage(quint32)),
            Qt::AutoConnection);
    // m_reporter->testHasFailed("NOT IMPLEMENTED!");

    if (not m_semaphore.tryAcquire(1, 5000))
    {
        m_reporter->testHasFailed(
            QString("No reponse from IOC or max value (%1) below threshold (%2)")
            .arg(m_maxReceived).arg(m_threshold));
    }
}
