#ifndef INPUTEVENTHANDLER_H
#define INPUTEVENTHANDLER_H

#include <QObject>
#include <QSocketNotifier>

class InputEventHandler
    : public QObject
{
    Q_OBJECT
public:
    explicit InputEventHandler(const int fd, int code, QObject *parent = 0);
    virtual ~InputEventHandler();

signals:
    void gotEvent(int value);

private slots:
    void readInputEvent(int socket);

private:
    int m_fd;
    QSocketNotifier *m_notifier;
    int m_code;
};

#endif /* INPUTEVENTHANDLER_H */
