#ifndef SAFEGUARDPOWER_H
#define SAFEGUARDPOWER_H

#include <QThread>

class InputEventHandler;
class IOCtrlCommController;

class SafeguardPower
    : public QThread
{
    Q_OBJECT
public:
    explicit SafeguardPower(IOCtrlCommController *ctrl, QObject *parent = 0);
    ~SafeguardPower();

protected:
    void run();

private slots:
    void onInputEvent(int value);

private:
    int m_fd;
    IOCtrlCommController *m_ctrl;
    InputEventHandler *m_inputs;
};

#endif /* SAFEGUARDPOWER_H */
