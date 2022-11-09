include ( ../../prod.pri )
TEMPLATE = lib

TARGET = IOCGpio
QT += \
    core \

QT -= gui

DEFINES += IOCGPIO_SHAREDLIB_LIBRARY
INCLUDEPATH += ../../include
HEADERS += \
    gpio.h

LIBS += -lgpiodcxx

SOURCES += \
    gpio.cpp

OTHER_FILES =


# Set install pats
target.path = $$VS_LIB_PATH
INSTALLS += target
