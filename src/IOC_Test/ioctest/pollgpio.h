#ifndef POLLGPIO_H
#define POLLGPIO_H

#include <QObject>
#include <QTimer>
#include "ioctrlcommController.h"

class PollGPIO
    : public QObject
{
    Q_OBJECT
public:
    explicit PollGPIO(IOCtrlCommController *ioc,
                      quint16 channel,
                      QObject *parent = 0);
    virtual ~PollGPIO();

private slots:
    void newValue(quint16 channel, quint16 value);
    void requestValue();

private:
    IOCtrlCommController *m_ioc;
    QTimer *m_timer;
    quint16 m_channel;
    quint16 m_lastValue;
};

#endif /* POLLGPIO_H */
