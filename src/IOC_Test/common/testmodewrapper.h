#ifndef TESTMODEWRAPPER_H
#define TESTMODEWRAPPER_H

#include <QObject>

class IOCtrlCommController;

class TestModeWrapper
    : public QObject
{
    Q_OBJECT

public:
    explicit TestModeWrapper(IOCtrlCommController *ctrl);
    ~TestModeWrapper();

private:
    IOCtrlCommController *_ctrl;
};

#endif /* TESTMODEWRAPPER_H */
