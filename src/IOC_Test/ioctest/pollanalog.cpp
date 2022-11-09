#include "pollanalog.h"

#include <QDebug>

PollAnalog::PollAnalog(IOCtrlCommController *ioc,
                 quint16 channel,
                 QObject *parent)
    : QObject(parent)
    , m_ioc(ioc)
    , m_channel(actualChannel(channel))
{
    connect(ioc, SIGNAL(adcMessage(quint16, quint16)),
            this, SLOT(newValue(quint16, quint16)));

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()),
            this, SLOT(requestValue()));
    m_timer->start(1000);

    m_ioc->sendTestModeCMD(0x01); // on
}

PollAnalog::~PollAnalog()
{
    m_ioc->disconnect(this);
    delete m_timer;
    m_ioc->sendTestModeCMD(0x02); // off
}

quint16 PollAnalog::actualChannel(quint16 ch)
{
    switch (ch)
    {
    case 1: return 11;
    case 2: return 12;
    case 3: return 4;
    case 4: return 15;
    case 5: return 8;
    case 6: return 9;
    default:
        return 0;
    }
}

void PollAnalog::newValue(quint16 channel, quint16 value)
{
    if (channel == m_channel)
    {
        qDebug() << "PollAnalog:" << channel
                 << "value:" << value;
    }
}

void PollAnalog::requestValue()
{
    m_ioc->sendTestGetAdcCMD(m_channel);
}
