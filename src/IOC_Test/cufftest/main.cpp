#include "cufftester.h"

#include <QtCore/QCoreApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CuffTester ct(&a);
    return a.exec();
}
