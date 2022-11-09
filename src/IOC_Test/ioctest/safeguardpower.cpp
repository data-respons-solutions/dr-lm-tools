#include "safeguardpower.h"

#include <QDebug>
#include "fcntl.h"
#include <unistd.h>

#include "inputeventhandler.h"
#include "ioctrlcommController.h"

SafeguardPower::SafeguardPower(IOCtrlCommController *ctrl, QObject *parent)
    : QThread(parent)
    , m_fd(0)
    , m_ctrl(ctrl)
    , m_inputs(0)
{
    m_fd = open("/dev/input/event0", O_RDONLY);
    if (m_fd < 0)
    {
        qDebug() << "Unable to open event stream. Run with root privileges";
        return;
    }
}

SafeguardPower::~SafeguardPower()
{
    if (m_fd >= 0)
    {
        close(m_fd);
        delete m_inputs;
    }
}

void SafeguardPower::onInputEvent(int value)
{
    if (value == 1)
    {
        m_ctrl->sendTestSetIOCMD(3, 0x01); // off
        qDebug() << ">>> power triggered! Tried to lower GPIO2";
    }
}

void SafeguardPower::run()
{
    m_inputs = new InputEventHandler(m_fd, 116);
    connect(m_inputs, SIGNAL(gotEvent(int)),
            this, SLOT(onInputEvent(int)),
            Qt::AutoConnection);
    qDebug() << "SafeguardPower: go!";
    exec();
}
