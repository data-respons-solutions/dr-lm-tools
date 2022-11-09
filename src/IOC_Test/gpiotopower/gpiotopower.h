#ifndef GPIOTOPOWER_H
#define GPIOTOPOWER_H

#include <QCoreApplication>
#include <QSemaphore>
#include <QTimer>
#include "inputeventhandler.h"
#include "ioctrlcommController.h"

class GpioToPower
    : public QCoreApplication
{
    Q_OBJECT
public:
    explicit GpioToPower(int &argc, char *argv[]);
    virtual ~GpioToPower();

public slots:
    void goImpl();
    void setReturnCode(int returnCode);
    void quitApplication();

private slots:
    void onEventSignalOk(int value);
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
    QTimer *m_powerTimer;
};

#endif /* GPIOTOPOWER_H */
