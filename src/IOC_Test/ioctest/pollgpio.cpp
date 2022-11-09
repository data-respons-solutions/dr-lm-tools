#include "pollgpio.h"

#include <QDebug>

PollGPIO::PollGPIO(IOCtrlCommController *ioc,
                   quint16 channel,
                   QObject *parent)
    : QObject(parent)
    , m_ioc(ioc)
    , m_channel(channel)
    , m_lastValue(0)
{
    connect(ioc, SIGNAL(gpioMessage(quint16, quint16)),
            this, SLOT(newValue(quint16, quint16)));

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()),
            this, SLOT(requestValue()));
    m_timer->start(100);

    m_ioc->sendTestModeCMD(0x01); // on
}

PollGPIO::~PollGPIO()
{
    m_ioc->disconnect(this);
    delete m_timer;
    m_ioc->sendTestModeCMD(0x02); // off
}

void PollGPIO::newValue(quint16 channel, quint16 value)
{
    if (channel == m_channel)
    {
        m_lastValue = value;
        qDebug() << "PollGPIO:" << channel
                 << "value:" << value;
    }
}

void PollGPIO::requestValue()
{
    m_ioc->sendTestGetIOCMD(m_channel);
}
