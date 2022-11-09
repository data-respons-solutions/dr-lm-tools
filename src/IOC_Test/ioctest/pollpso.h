#ifndef POLLPSO_H
#define POLLPSO_H

#include <QObject>
#include <QTimer>
#include "ioctrlcommController.h"

class PollPSO
    : public QObject
{
    Q_OBJECT
public:
    explicit PollPSO(IOCtrlCommController *ioc,
                     quint16 channel,
                     QObject *parent = 0);
    virtual ~PollPSO();

private slots:
    void newValue(quint16 channel, quint32 value);
    void requestValue();

private:
    IOCtrlCommController *m_ioc;
    QTimer *m_timer;
    quint16 m_channel;
    quint16 m_lastFreq;
};

#endif /* POLLPSO_H */
