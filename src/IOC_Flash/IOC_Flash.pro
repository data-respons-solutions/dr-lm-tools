#-------------------------------------------------
#
# Project created by QtCreator 2010-12-17T09:40:33
#
#-------------------------------------------------
include ( ../prod.pri )
TEMPLATE = app
CONFIG += console
TARGET = iocflash

QT += core
QT -= gui

# The VitalSim2 setup
#include ( ../../mkspecs/SimPad.pri )


#CONFIG   -= app_bundle

INCLUDEPATH += ../include

# qextserialport Library
QEXTSERIALPORT_BUILDDIR = ../libs/qextserialport
include( ../libs/qextserialport/qextserialport.pri )

# libVSCommon Library
LIBVSCOMMON_BUILDDIR = ../libs/libVSCommon
include( ../libs/libVSCommon/libVSCommon.pri )

# libIOCGpio Library
LIBIOCGPIO_BUILDDIR = ../libs/libIOCGpio
include( ../libs/libIOCGpio/libIOCGpio.pri )

# Set inst# Set install pats
target.path = $$VS_BIN_PATH
INSTALLS += target

extra.path = $$VS_CONF_PATH
INSTALLS += extra


INCLUDEPATH += . ../Common

SOURCES += main.cpp \
    ioctrlcommcontroller.cpp \
    iocontrollerupdatethread.cpp \
    iocontrollercommthread.cpp

HEADERS += \
    ioctrlcommcontroller.h \
    iocontrollerupdatethread.h \
    SWversion.h \
    iocontrollercommthread.h
