
PROJECT                 = qextserialport
TEMPLATE                = lib
VERSION                 = 1.2.0
DESTDIR                 = build
CONFIG                 += qt warn_on
CONFIG                  += dll
DEFINES                 += QEXTSERIALPORT_LIB
#CONFIG                 += staticlib
include ( ../../../prod.pri )
# event driven device enumeration on windows requires the gui module
!win32:QT               -= gui

# SSe: Disable for VS2:
#OBJECTS_DIR             = tmp
#MOC_DIR                 = tmp
DEPENDDIR               = .
INCLUDEDIR              = .
HEADERS                 = qextserialport.h \
                          qextserialenumerator.h \
                          qextserialport_global.h
SOURCES                 = qextserialport.cpp

unix:SOURCES           += posix_qextserialport.cpp
unix:!macx:SOURCES     += qextserialenumerator_unix.cpp
macx {
  SOURCES          += qextserialenumerator_osx.cpp
  LIBS             += -framework IOKit -framework CoreFoundation
}

win32 {
  SOURCES          += win_qextserialport.cpp qextserialenumerator_win.cpp
  DEFINES          += WINVER=0x0501 # needed for mingw to pull in appropriate dbt business...probably a better way to do this
  LIBS             += -lsetupapi -ladvapi32 -lUser32
}

CONFIG(debug, debug|release) {
    TARGET = qextserialportd
} else {
    TARGET = qextserialport
}


#
# VitalSim2 modifications:
#


# Set install pats
target.path = $$VS_LIB_PATH
INSTALLS += target
