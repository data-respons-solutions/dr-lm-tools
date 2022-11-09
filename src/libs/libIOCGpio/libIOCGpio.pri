QT += core \

# Headers are located in this location (where the project is)
INCLUDEPATH += $$PWD
INCLUDEPATH += ../../include
DEPENDPATH += include $$PWD

# Link against libiocgpio
!contains(LIBIOCGPIO_BUILDDIR,$$OUT_PWD): LIBIOCGPIO_BUILDDIR=$$OUT_PWD/$$LIBIOCGPIO_BUILDDIR
isEmpty(LIBIOCGPIO_BUILDDIR): LIBIOCGPIO_BUILDDIR=$$OUT_PWD

LIBS += -L$$LIBIOCGPIO_BUILDDIR/$$DESTDIR -lIOCGpio
isEmpty(VS_CROSS):LIBS += -Wl,-rpath,$$LIBIOCGPIO_BUILDDIR/$$DESTDIR