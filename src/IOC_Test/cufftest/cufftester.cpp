#include "cufftester.h"
#include "ioctrlcommController.h"

#include <QTimer>

CuffTester::CuffTester(QObject *parent) :
    QObject(parent)
{
    ioControl = new IOCtrlCommController("/dev/ttymxc3");

    connect(ioControl, SIGNAL(cuffMessage(quint32)),
            this, SLOT(printCuffValue(quint32)));

    QTimer::singleShot(10000, parent, SLOT(quit()));
}

void CuffTester::printCuffValue(quint32 value)
{
    qDebug("Cuff value received: %d", value);
}

