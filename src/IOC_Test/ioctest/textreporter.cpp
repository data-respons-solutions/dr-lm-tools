#include "textreporter.h"

#include <QDebug>
#include <QHashIterator>

TextReporter::TextReporter(QCoreApplication *app,
                           bool colorized,
                           QObject *parent)
    : QObject(parent)
    , m_currentTest()
    , m_application(app)
    , m_current(0)
    , m_tests()
    , m_colorized(colorized)
{
}

void TextReporter::setCurrentTestName(QString name)
{
    // if (m_okTable.contains(name))
    // {
    //     qDebug() << QString("The test %1 is already run").arg(name);
    //     return;
    // }
    m_current = new TestData();
    m_current->name = name;
    m_current->ok = true;
    m_current->why = QString();
    // m_tests.append();
    // m_currentTest = name;
    // m_okTable[name] = true;     // assume good
    // m_errorTable[name] = "";
}

void TextReporter::testHasFailed(QString why)
{
    m_current->ok = false;
    m_current->why = why;
    // m_okTable[m_currentTest] = false;

    qDebug("%s failed:\n    %s",
           m_current->name.toUtf8().constData(),
           why.toUtf8().constData());
    // m_errorTable[m_currentTest] = why;
}

void TextReporter::testHasRun()
{
    // m_okTable[m_currentTest] = true;
    m_tests.append(m_current);
    // m_currentTest = "NULL";
}

bool TextReporter::allTestsPassed()
{
    return getFailedCount() == 0;
}

quint32 TextReporter::getFailedCount()
{
    quint32 count = 0;
    QList<TestData*>::const_iterator it;
    for (it = m_tests.begin(); it != m_tests.end(); ++it)
    {
        if (not (*it)->ok)
            count++;
    }
    return count;
}

void TextReporter::printTestResults(bool verbose)
{
    const char * red    = m_colorized ? "\033[31;1m" : "";
    const char * green  = m_colorized ? "\033[32;1m" : "";
    const char * normal = m_colorized ? "\033[0m"    : "";
    const char * bold   = m_colorized ? "\033[1m"    : "";

    quint32 failedCount = getFailedCount();

    qDebug("\n=====\n\nTest summary:");  // TODO bold
    qDebug("    Tests executed: %3d", m_tests.count());
    qDebug("    Tests passed:   %3d", (m_tests.count() - failedCount));

    if (failedCount == 0)     // ok
    {
        qDebug("    Tests failed:   %s%3d%s", green, failedCount, normal);
        qDebug("\n    %sAll tests passed!%s", green, normal);
    }
    else
    {
        qDebug("    Tests failed:   %s%3d%s", red, failedCount, normal);
        // qDebug("%sSome tests failed:%s", red, normal);
        // QHashIterator<QString, bool> it(m_okTable);
        // while (it.findNext(false))
        // {
        //     qDebug("    %s", it.key().toUtf8().data());
        // }
    }

    if (verbose)
    {
        qDebug("\nTest overview:"); // TODO bold
    }
    else
    {
        qDebug("\nFailed tests:");
    }
    QList<TestData*>::const_iterator it;
    for (it = m_tests.begin();
         it != m_tests.end();
         ++it)
    {
        if ((*it)->ok)
        {
            if (verbose)
            {
                qDebug("    %s: %s%s%s",
                       (*it)->name.toUtf8().constData(),
                       green, "OK", normal);
            }
        }
        else
        {
            qDebug("    %s: %s%s%s",
                   (*it)->name.toUtf8().constData(),
                   red, "FAILED", normal);
        }
    }
}
