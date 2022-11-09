#include "powertogpio.h"

#include <QDebug>
#include <fcntl.h>
#include "inputeventhandler.h"

PowerToGpio::PowerToGpio(int &argc, char *argv[])
    : QCoreApplication(argc, argv)
    , m_returnCode(0)
    , m_count(0)
    , m_inputs(0)
    , m_event(0)
    , m_waitingForEvent(false)
    , m_waitingForGpio(false)
{
    m_fd = open("/dev/input/event0", O_RDONLY);
    if (m_fd < 0)
    {
        qDebug() << "Unable to open event stream.";
        return;
    }

    m_ioc = new IOCtrlCommController("/dev/ttymxc3");
    m_ioc->sendTestModeCMD(1);  // on

    m_inputs = new InputEventHandler(m_fd, 116, this);
    connect(this, SIGNAL(go()),
            this, SLOT(goImpl()),
            Qt::QueuedConnection);
    emit go();
}

PowerToGpio::~PowerToGpio()
{
    m_ioc->sendTestModeCMD(2);  // off
    if (m_fd >= 0)
    {
        close(m_fd);
        delete m_inputs;
    }
}

void PowerToGpio::setReturnCode(int returnCode)
{
    m_returnCode = returnCode;
}

void PowerToGpio::quitApplication()
{
    exit(m_returnCode);
}

// Main logic

void PowerToGpio::goImpl()
{
    qDebug() << "Press power button!";

    connect(m_inputs, SIGNAL(gotEvent(int)),
            this, SLOT(gotEventImpl(int)),
            Qt::QueuedConnection);
    connect(m_ioc, SIGNAL(gpioMessage(quint16, quint16)),
            this, SLOT(newGpioValue(quint16, quint16)),
            Qt::QueuedConnection);

    connect(this, SIGNAL(success()),
            this, SLOT(successImpl()),
            Qt::QueuedConnection);

    m_waitingForEvent = true;

    QTimer::singleShot(5000, this, SLOT(timeout()));
}

void PowerToGpio::successImpl()
{
    qDebug() << "Success!";
    setReturnCode(0);
    QTimer::singleShot(100, this, SLOT(quitApplication()));
}

void PowerToGpio::timeout()
{
    qDebug() << "No response.";
    m_waitingForEvent = false;
    setReturnCode(1);
    QTimer::singleShot(100, this, SLOT(quitApplication()));
}

void PowerToGpio::gotEventImpl(int value)
{
    if (value == 1)
    {
        if (m_waitingForEvent)
        {
            qDebug() << "(waiting for event)";
            m_waitingForEvent = false;
            m_waitingForGpio = true;
            m_ioc->sendTestGetIOCMD(3);
        }
    }
}

void PowerToGpio::newGpioValue(quint16 channel, quint16 value)
{
    if (channel == 3
        && m_waitingForGpio
        && value == 1)
    {
        m_waitingForGpio = false;
        emit success();
    }
}
