#include "testmodewrapper.h"

#include "ioctrlcommController.h"

TestModeWrapper::TestModeWrapper(IOCtrlCommController *ctrl)
    : _ctrl(ctrl)
{
    _ctrl->sendTestModeCMD(0x01); // on
}

TestModeWrapper::~TestModeWrapper()
{
    _ctrl->sendTestModeCMD(0x02); // off
}
