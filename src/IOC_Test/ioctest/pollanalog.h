#ifndef POLLANALOG_H
#define POLLANALOG_H

#include <QObject>
#include <QTimer>
#include "ioctrlcommController.h"

class PollAnalog
    : public QObject
{
    Q_OBJECT
public:
    explicit PollAnalog(IOCtrlCommController *ioc,
                     quint16 channel,
                     QObject *parent = 0);
    virtual ~PollAnalog();

private slots:
    void newValue(quint16 channel, quint16 value);
    void requestValue();
    quint16 actualChannel(quint16 ch);

private:
    IOCtrlCommController *m_ioc;
    QTimer *m_timer;
    quint16 m_channel;
};

#endif /* POLLANALOG_H */
