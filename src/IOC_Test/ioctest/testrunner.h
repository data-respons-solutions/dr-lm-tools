#ifndef TESTRUNNER_H
#define TESTRUNNER_H

#include <QObject>
#include <QThread>
#include <QCoreApplication>
#include "itestcase.h"
#include "textreporter.h"

class TestRunner
    : public QThread
{
    Q_OBJECT
public:
    explicit TestRunner(QCoreApplication *app,
                        TextReporter *reporter,
                        QObject *parent = 0);

public slots:
    void addTest(ITestCase *test);
    void runTests();
    void add(const QList<ITestCase *> &tests);

private:
    void run();
    QCoreApplication *m_application;
    TextReporter *m_reporter;
    QList<ITestCase *> m_tests;
};

#endif /* TESTRUNNER_H */
