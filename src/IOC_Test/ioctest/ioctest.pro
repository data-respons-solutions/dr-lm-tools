TEMPLATE = app
CONFIG += console
TARGET = ioctest


QT += core
QT -= gui

include ( ../../prod.pri )
INCLUDEPATH += ../../include

INCLUDEPATH += ../common
LIBS += -L../common -lcommon

INCLUDEPATH += ../../libs/qextserialport/src
LIBS += -L../../libs/qextserialport/src/build -lqextserialport

INCLUDEPATH += ../../libs/libVSCommon
LIBS += -L../../libs/libVSCommon -lVSCommon

# Input
HEADERS += \
	pollanalog.h \
	pollgpio.h \
	pollpso.h \
	safeguardpower.h \
	testanalog.h \
	testcancpr.h \
	testcuff.h \
	testgpio.h \
	testgpoecg.h \
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
	testcancpr.cpp \
	testcuff.cpp \
	testgpio.cpp \
	testgpoecg.cpp \
	testpower.cpp \
	testpso.cpp \
	testpulsedriver.cpp \
	testrunner.cpp \
	textreporter.cpp
