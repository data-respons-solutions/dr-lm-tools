#ifndef TEXTREPORTER_H
#define TEXTREPORTER_H

#include <QCoreApplication>
#include <QHash>
#include "itestreporter.h"

class TextReporter
    : public QObject,
      public ITestReporter
{
    Q_OBJECT
public:
    explicit TextReporter(QCoreApplication *app,
                          bool colorized = false,
                          QObject *parent = 0);

public slots:
    virtual void setCurrentTestName(QString name);
    virtual void testHasFailed(QString why);
    virtual void testHasRun();
    virtual bool allTestsPassed();

    void printTestResults(bool verbose);

private slots:
    quint32 getFailedCount();

private:
    QString m_currentTest;
    QCoreApplication *m_application;
    struct TestData
    {
        QString name;
        bool ok;
        QString why;
    };
    TestData *m_current;
    QList<TestData*> m_tests;
    // QHash<QString, bool> m_okTable;
    // QHash<QString, QString> m_errorTable;
    bool m_colorized;
};

#endif /* TEXTREPORTER_H */
