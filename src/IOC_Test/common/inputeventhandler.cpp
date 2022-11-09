#include "inputeventhandler.h"

#include <linux/input.h>
#include <unistd.h>
#include <QDebug>

InputEventHandler::InputEventHandler(const int fd, int code, QObject * parent)
    : QObject(parent)
    , m_fd(fd)
    , m_notifier(0)
    , m_code(code)
{
    m_notifier = new QSocketNotifier(m_fd, QSocketNotifier::Read, parent);
    connect(m_notifier, SIGNAL(activated(int)),
            this, SLOT(readInputEvent(int)));
    m_notifier->setEnabled(true);
}

InputEventHandler::~InputEventHandler()
{
    m_notifier->disconnect(SIGNAL(activated(int)));
    delete m_notifier;
}

// ignore argument as we only attach to one fd
void InputEventHandler::readInputEvent(int)
{
    input_event ev;
    int n = read(m_fd, &ev, sizeof(input_event));
    if (n == sizeof(input_event)
        && ev.type != 0
        && ev.code == m_code)
    {
        emit gotEvent(ev.value);
    }
}
