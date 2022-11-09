#ifndef POWERTOGPIO_H
#define POWERTOGPIO_H

#include <QCoreApplication>
#include <QSemaphore>
#include <QTimer>
#include "inputeventhandler.h"
#include "ioctrlcommController.h"

class PowerToGpio
    : public QCoreApplication
{
    Q_OBJECT
public:
    explicit PowerToGpio(int &argc, char *argv[]);
    virtual ~PowerToGpio();

public slots:
    void goImpl();
    void setReturnCode(int returnCode);
    void quitApplication();

private slots:
    void newGpioValue(quint16 channel, quint16 value);
    void gotEventImpl(int value);
    void successImpl();
    void timeout();

signals:
    void go();
    void success();

private:
    int m_returnCode;
    int m_fd;
    int m_count;
    InputEventHandler *m_inputs;
    IOCtrlCommController *m_ioc;
    QSemaphore m_event;
    bool m_waitingForEvent;
    bool m_waitingForGpio;
    QTimer *m_powerTimer;
};

#endif /* POWERTOGPIO_H */
