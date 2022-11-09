######################################################################
# Automatically generated by qmake (2.01a) Tue Jul 12 14:50:02 2011
######################################################################

TEMPLATE = app
TARGET = gpiotopower
DEPENDPATH += .
INCLUDEPATH += .

QT -= gui
include ( ../../prod.pri )
# install paths
target.path = $$VS_BIN_PATH
INSTALLS += target

extra.path = $$VS_CONF_PATH
INSTALLS += extra

INCLUDEPATH += ../common
LIBS += -L../common -lcommon

# qextserialport Library
QEXTSERIALPORT_BUILDDIR = ../../libs/qextserialport
include( ../../libs/qextserialport/qextserialport.pri )

# libVSHAL Library for Base Unit
LIBVSHAL_BUILDDIR = ../../libs/libVSHAL
LIBVSHAL_BU = 1
include( ../../libs/libVSHAL/libVSHAL.pri )
# libVSCommon Library
LIBVSCOMMON_BUILDDIR = ../../libs/libVSCommon
include( ../../libs/libVSCommon/libVSCommon.pri )

# Input
HEADERS += \
        gpiotopower.h

SOURCES += \
        main.cpp \
        gpiotopower.cpp