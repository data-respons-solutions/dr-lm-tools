#ifndef TESTGPIO_H
#define TESTGPIO_H

#include <QThread>
#include <QSemaphore>
#include "ioctrlcommController.h"

#include "itestcase.h"
#include "itestreporter.h"

class TestGPIO
    : public QObject,
      public ITestCase
{
    Q_OBJECT
public:
    explicit TestGPIO(IOCtrlCommController * controller,
                      quint16 readChannel,
                      quint16 writeChannel,
                      QObject *parent = 0);
public:
    virtual QString getName() const;
    virtual void setReporter(ITestReporter *reporter);
    virtual void runTest();

private slots:
    void receivedGpioMessage(quint16 channel, quint16 value);

private:
    quint16 actualChannel(quint16 ch);

    IOCtrlCommController *m_controller;
    ITestReporter *m_reporter;
    QSemaphore m_semaphore;
    quint16 m_writeChannel;
    quint16 m_readChannel;
    quint16 m_receivedValue;
};

#endif /* TESTGPIO_H */
