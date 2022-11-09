#ifndef PULSEDRIVER_H
#define PULSEDRIVER_H

#include <QCoreApplication>

class IOCtrlCommController;

class PulseDriver
    : public QCoreApplication
{
    Q_OBJECT
public:
    explicit PulseDriver(int &argc, char *argv[]);
    virtual ~PulseDriver();

public slots:
    void setReturnCode(int code) { m_returnCode = code; }
    void quitApplication() { exit(m_returnCode); }

signals:
    void go();
    void getValue();

private slots:
    void goImpl();
    void getValueImpl();
    void setPwmImpl();
    void newAnalogValue(quint16 channel, quint16 value);

private:
    int m_returnCode;
    IOCtrlCommController *m_ioc;
    int m_which;

    // options
    bool m_invert;
    quint16 m_pwmValue;
};

#endif /* PULSEDRIVER_H */
