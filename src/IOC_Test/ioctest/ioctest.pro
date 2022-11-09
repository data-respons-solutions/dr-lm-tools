TEMPLATE = app
CONFIG += debug_and_release console
TARGET = ioctest


QT += core
QT -= gui

include ( ../../prod.pri )
# install paths
target1.files = ioctestsdfds
target1.path = $$VS_BIN_PATH
INSTALLS += target1

extra.path = $$VS_CONF_PATH
INSTALLS += extra

INCLUDEPATH += ../common
LIBS += -L../common -lcommon

# qextserialport Library
QEXTSERIALPORT_BUILDDIR = ../../libs/qextserialport
include( ../../libs/qextserialport/qextserialport.pri )

# libVSCommon Library
LIBVSCOMMON_BUILDDIR = ../../libs/libVSCommon
include( ../../libs/libVSCommon/libVSCommon.pri )


# Input
HEADERS += \
	pollanalog.h \
	pollgpio.h \
	pollpso.h \
	safeguardpower.h \
	testanalog.h \
	testcuff.h \
	testgpio.h \
	testgpo.h \
	testpower.h \
	testpso.h \
	testpulsedriver.h \
	testrunner.h \
	textreporter.h \

SOURCES += \
	main.cpp \
	pollanalog.cpp \
	pollgpio.cpp \
	pollpso.cpp \
	safeguardpower.cpp \
	testanalog.cpp \
	testcuff.cpp \
	testgpio.cpp \
	testgpo.cpp \
	testpower.cpp \
	testpso.cpp \
	testpulsedriver.cpp \
	testrunner.cpp \
	textreporter.cpp
