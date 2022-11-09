#ifndef TESTPSO_H
#define TESTPSO_H

#include <QString>
#include <QSemaphore>
#include "itestcase.h"
#include "ioctrlcommController.h"

// Assumes that the detectors are detecting.
class TestPSO
    : public QObject,
      public ITestCase
{
    Q_OBJECT
public:
    explicit TestPSO(IOCtrlCommController *controller,
                     quint16 channel,     // 1..6
                     quint32 expectedFreq,
                     QObject *parent = 0);
    
public:
    virtual QString getName() const;
    virtual void setReporter(ITestReporter *reporter);
    virtual void runTest();

private slots:
    void receivedPulseMessage(quint16 channel, quint32 frequency);

private:
    bool closeEnough(quint32 input, quint32 target);
    quint16 ioChannel(quint16 ch);

    IOCtrlCommController *m_controller;
    ITestReporter *m_reporter;
    quint16 m_channel;

    QSemaphore m_semaphore;
    quint32 m_expectedFreq;
    quint32 m_receivedFreq;
};

#endif /* TESTPSO_H */
