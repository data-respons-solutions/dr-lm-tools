# Headers are located in this location (where the project is)
INCLUDEPATH += $$PWD/src

win32:{
    DEFINES += _TTY_WIN_

    CONFIG(release, debug|release):SUFFIX=1
    CONFIG(debug, debug|release):SUFFIX=d1
}
unix:{
    DEFINES += _TTY_POSIX_

    CONFIG(debug, debug|release):SUFFIX=d
}

# Link against qextserialport
!contains(QEXTSERIALPORT_BUILDDIR,$$OUT_PWD): QEXTSERIALPORT_BUILDDIR=$$OUT_PWD/$$QEXTSERIALPORT_BUILDDIR
isEmpty(QEXTSERIALPORT_BUILDDIR): QEXTSERIALPORT_BUILDDIR=$$OUT_PWD
LIBS += -L$$QEXTSERIALPORT_BUILDDIR/src/build -lqextserialport$$SUFFIX
isEmpty(VS_CROSS):LIBS += -Wl,-rpath,$$QEXTSERIALPORT_BUILDDIR/src/build
