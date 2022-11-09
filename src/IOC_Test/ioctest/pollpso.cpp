#include "pollpso.h"

#include <QDebug>

PollPSO::PollPSO(IOCtrlCommController *ioc,
                 quint16 channel,
                 QObject *parent)
    : QObject(parent)
    , m_ioc(ioc)
    , m_channel(channel)
    , m_lastFreq(0)
{
    connect(ioc, SIGNAL(pulseMessage(quint16, quint32)),
            this, SLOT(newValue(quint16, quint32)));

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()),
            this, SLOT(requestValue()));
    m_timer->start(1000);

    m_ioc->sendTestModeCMD(0x01); // on
}

PollPSO::~PollPSO()
{
    m_ioc->disconnect(this);
    delete m_timer;
    m_ioc->sendTestModeCMD(0x02); // off
}

void PollPSO::newValue(quint16 channel, quint32 freq)
{
    if (channel == m_channel)
    {
        m_lastFreq = freq;
        qDebug() << "PollPSO:" << channel
                 << "freq:" << freq;
    }
}

void PollPSO::requestValue()
{
    m_ioc->sendTestGetPulsePalpFreqCMD(m_channel);
}
