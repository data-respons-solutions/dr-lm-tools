#include "pulsedriver.hpp"

#include <QStringList>
#include <QTimer>
#include "ioctrlcommController.h"

PulseDriver::PulseDriver(int &argc, char *argv[])
    : QCoreApplication(argc, argv)
    , m_returnCode(0)
    , m_ioc(0)
    , m_which(-1)
    , m_invert(false)
    , m_pwmValue(0x1000)        // default
{
    m_ioc = new IOCtrlCommController("/dev/ttymxc3");
    m_ioc->sendTestModeCMD(0x01); // on

    QString arg;
    Q_FOREACH(arg, arguments())
    {
        if (arg == "-i")
        {
            m_invert = true;
        }
        if (arg.startsWith("--value="))
        {
            bool ok;
            quint16 v = arg.mid(8).toUInt(&ok, 0);
            if (ok)
                m_pwmValue = v;
        }
    }
    qDebug().nospace() << "Options: -i:" << m_invert
                       << ", value=" << m_pwmValue;

    connect(this, SIGNAL(go()),
            this, SLOT(goImpl()),
            Qt::QueuedConnection);
    emit go();
}

PulseDriver::~PulseDriver()
{
    m_ioc->sendTestModeCMD(0x02);
    delete m_ioc;
}

void PulseDriver::goImpl()
{
    connect(this, SIGNAL(getValue()),
            this, SLOT(getValueImpl()),
            Qt::AutoConnection);
    connect(m_ioc, SIGNAL(adcMessage(quint16, quint16)),
            this, SLOT(newAnalogValue(quint16, quint16)),
            Qt::QueuedConnection);
    m_ioc->sendTestSetIOCMD(3, 0x01);
    emit getValue();
}

void PulseDriver::getValueImpl()
{
    m_ioc->sendTestGetAdcCMD(11); // analog_in1
    if (m_which > 6)
    {
        QTimer::singleShot(100, this, SLOT(quitApplication()));
    }
    else
    {
        QTimer::singleShot(200, this, SLOT(setPwmImpl()));
    }
}

void PulseDriver::newAnalogValue(quint16 channel, quint16 value)
{
    qDebug() << "PulseDriver channel" << channel
             << "value" << value;
    m_which++;                  // next pdo
}

void PulseDriver::setPwmImpl()
{
    for (quint16 i = 1; i <= 6; ++i)
    {
        quint16 pwm = ((i == m_which) ^ m_invert) ? m_pwmValue : 0x0000;
        qDebug() << "Set PWM" << i << "to" << pwm;
        m_ioc->sendTestSetPwmCMD(i-1, pwm);
    }
    QTimer::singleShot(500, this, SLOT(getValueImpl()));
}
