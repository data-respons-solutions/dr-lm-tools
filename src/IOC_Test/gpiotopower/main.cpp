#include <stdio.h>
#include "gpiotopower.h"

int main(int argc, char *argv[])
{
    GpioToPower app(argc, argv);
    return app.exec();
}
