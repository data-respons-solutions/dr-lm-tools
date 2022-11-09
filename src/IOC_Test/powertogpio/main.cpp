#include "powertogpio.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    PowerToGpio app(argc, argv);
    return app.exec();
}
