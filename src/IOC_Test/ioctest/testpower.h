#ifndef TESTPOWER_H
#define TESTPOWER_H

#include <QObject>
#include <QString>
#include <QSemaphore>
#include <QSocketNotifier>

#include "ioctrlcommController.h"
#include "itestcase.h"

class TestPower
    : public QObject,
      public ITestCase
{
    Q_OBJECT
public:
    explicit TestPower(IOCtrlCommController * controller,
                       quint16 timeout,
                       QObject *parent = 0);

public:
    virtual QString getName() const;
    virtual void setReporter(ITestReporter *reporter);
    virtual void runTest();

private slots:
    void receivedMessage(quint16 channel, quint16 value);
    void signalSemaphore(int value);
    void readGPIO(int value);
    void runTest0();
    void runTest1();
    void runTest2();

private:
    IOCtrlCommController *m_controller;
    ITestReporter *m_reporter;

    quint16 m_channel;
    quint16 m_receivedValue;
    quint16 m_timeout;

    QSemaphore m_IOCcomm;
    QSemaphore m_powerEvent;

    // for reading power button
    int m_fd;
    int m_count;
};

#endif /* TESTPOWER_H */
