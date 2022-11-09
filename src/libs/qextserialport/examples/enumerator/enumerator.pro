######################################################################
# Enumerator
######################################################################


PROJECT = enumerator
TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH  += ../../src
QMAKE_LIBDIR += ../../src/build

OBJECTS_DIR    = tmp
MOC_DIR        = tmp
UI_DIR         = tmp

SOURCES += main.cpp

CONFIG(debug, debug|release):LIBS  += -lqextserialportd1
else:LIBS  += -lqextserialport1
win32:LIBS += -lsetupapi
