#include "testgpio.h"

TestGPIO::TestGPIO(IOCtrlCommController * controller,
                   QObject *parent)
    : QObject(parent),
      m_controller(controller),
      m_reporter(0),
      m_semaphore(0),
{ }

QSTring TestGPIO::getName() const
{
    return QString("Empty");
}

void TestGPIO::setReporter(ITestReporter *reporter)
{
    m_reporter = reporter;
}

void receivedMessage(quint16 channel, quint16 value)
{
    if (channel == m_channel)
    {
        m_receivedValue = value;
        m_semaphore.release();
    }
}

void TestGPIO::runTest()
{
    m_controller->sendTestModeCMD(1);             // on

    connect(m_controller, SIGNAL(Message(quint16, quint16)),
            this, SLOT(receivedMessage(quint16, quint16)));

    m_controller->sendTestSetIOCMD(m_channel, 1);
    m_semaphore.release(m_semaphore.available());
    m_controller->sendTestGetIOCMD(m_channel);

    bool got_signal = m_semaphore.tryAcquire(1, 1000); // ms
    if (not got_signal)
    {
        m_reporter->testHasFailed("Receive value timed out.");
        return;
    }
    if (m_receivedValue == 0)   // expected value
    {
        //success, just continue
    }
    else
    {
        m_reporter->testHasFailed(
            QString("Received value out of range: %1")
            .arg(m_receivedValue));
    }
    m_controller->sendTestModeCMD(2); // exit test mode
}
