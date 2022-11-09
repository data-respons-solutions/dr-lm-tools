#ifndef TESTCUFF_H
#define TESTCUFF_H

#include <QObject>
#include <QSemaphore>

#include "ioctrlcommController.h"
#include "itestcase.h"

class TestCuff
    : public QObject,
      public ITestCase
{
    Q_OBJECT
public:
    explicit TestCuff(IOCtrlCommController * controller,
                      quint32 threshold,
                      QObject *parent = 0);

public:
    virtual QString getName() const;
    virtual void setReporter(ITestReporter *reporter);
    virtual void runTest();

private slots:
    void receivedMessage(quint32 value);

private:
    IOCtrlCommController *m_controller;
    ITestReporter *m_reporter;

    quint16 m_channel;
    quint32 m_maxReceived;
    quint32 m_threshold;

    QSemaphore m_semaphore;
};

#endif /* TESTCUFF_H */
