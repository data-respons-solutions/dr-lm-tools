TEMPLATE = app
TARGET = pso
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
# libVSCom Library
# libVSCommon Library
LIBVSCOMMON_BUILDDIR = ../../libs/libVSCommon
include( ../../libs/libVSCommon/libVSCommon.pri )

# Input
HEADERS += \
        pso.hpp

SOURCES += \
        main.cpp \
        pso.cpp

