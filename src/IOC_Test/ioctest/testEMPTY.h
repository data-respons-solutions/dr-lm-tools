#ifndef TESTEMPTY_H
#define TESTEMPTY_H

#include <QObject>
#include <QSemaphore>

#include "ioctrlcommController.h"
#include "itestcase.h"

class TestEMPTY
    : public QObject,
      public ITestCase
{
    Q_OBJECT
public:
    explicit TestEMPTY(IOCtrlCommController * controller,
                       // div args
                       QObject *parent = 0);

public:
    virtual QString getName() const;
    virtual void setReporter(ITestReporter *reporter);
    virtual void runTest();

private slots:
    void receivedMessage(quint16 channel, quint16 value);

private:
    IOCtrlCommController *m_controller;
    ITestReporter *m_reporter;

    quint16 m_channel;
    quint16 m_receivedValue;

    QSemaphore m_semaphore;
};

#endif /* TESTEMPTY_H */
