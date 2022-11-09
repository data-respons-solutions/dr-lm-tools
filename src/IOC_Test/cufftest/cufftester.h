#ifndef CUFFTESTER_H
#define CUFFTESTER_H

#include <QObject>

class IOCtrlCommController;

class CuffTester : public QObject
{
    Q_OBJECT
public:
    explicit CuffTester(QObject *parent = 0);

signals:
    void finished();

private slots:
    void printCuffValue(quint32 value);

private:
    IOCtrlCommController *ioControl;

};

#endif // CUFFTESTER_H
