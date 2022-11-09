# The VitalSim2 setup

include ( ../../prod.pri )
TEMPLATE = lib

TARGET = VSCommon
QT += \
    core \
    xml \
    network

QT -= gui

DEFINES += VSCOMMON_SHAREDLIB_LIBRARY
INCLUDEPATH += ../../include
HEADERS += \
    Communication/CrcCCITT.h \
    Communication/CommunicationIDs.h 

SOURCES += \
    Communication/CrcCCITT.cpp

OTHER_FILES =


# Set install pats
target.path = $$VS_LIB_PATH
INSTALLS += target
