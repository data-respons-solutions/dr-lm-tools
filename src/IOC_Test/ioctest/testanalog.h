#ifndef TESTANALOG_H
#define TESTANALOG_H

#include <QObject>
#include <QSemaphore>

#include "itestcase.h"
#include "ioctrlcommController.h"

class TestAnalog
    : public QObject,
      public ITestCase
{
    Q_OBJECT
public:
    explicit TestAnalog(IOCtrlCommController * controller,
                        quint16 channel, // 1..6
                        quint16 expectedLow,
                        quint16 expectedHigh,
                        QObject *parent = 0);

    virtual QString getName() const;
    virtual void setReporter(ITestReporter *reporter);
    virtual void runTest();

private slots:
    void receivedAdcMessage(quint16 channel, quint16 value);

private:
    quint16 actualChannel(quint16 ch);

    IOCtrlCommController *m_controller;
    ITestReporter *m_reporter;

    quint16 m_channel;
    quint16 m_expectedLow;
    quint16 m_expectedHigh;

    QSemaphore m_semaphore;
    quint16 m_receivedValue;
};

#endif // TESTANALOG_H
