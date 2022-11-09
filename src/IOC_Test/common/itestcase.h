#ifndef ITESTCASE_H
#define ITESTCASE_H

#include <QObject>
#include <QString>
#include "itestreporter.h"

class ITestCase
    // : public QObject
{
    // Q_OBJECT
public:
    virtual ~ITestCase() {}

    virtual QString getName() const = 0;
    virtual void setReporter(ITestReporter *reporter) = 0;
    virtual void runTest() = 0;
};

#endif // ITESTCASE_H
