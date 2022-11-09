#ifndef PSO_H
#define PSO_H

#include <QCoreApplication>
#include <QTimer>
#include "ioctrlcommController.h"

class PSO
    : public QCoreApplication
{
    Q_OBJECT
public:
    explicit PSO(int &argc, char *argv[]);
    virtual ~PSO();

public slots:
    void setReturnCode(int code);
    void quitApplication();

signals:
    void go();
    void getValue();

private slots:
    void goImpl();
    void getValueImpl();
    void newPsoValue(quint16 channel, quint32 value);

private:
    int m_returnCode;
    IOCtrlCommController *m_ioc;
    int m_count;

    // options
    int m_maxCount;
    int m_delay;
    quint16 m_readChannel;
};

#endif /* PSO_H */
