QT += core \
    xml \
    network

# Headers are located in this location (where the project is)
INCLUDEPATH += $$PWD
INCLUDEPATH += ../../include
DEPENDPATH += include $$PWD

# Link against VSCommon
!contains(LIBVSCOMMON_BUILDDIR,$$OUT_PWD): LIBVSCOMMON_BUILDDIR=$$OUT_PWD/$$LIBVSCOMMON_BUILDDIR
isEmpty(LIBVSCOMMON_BUILDDIR):LIBVSCOMMON_BUILDDIR=$$OUT_PWD

LIBS += -L$$LIBVSCOMMON_BUILDDIR/$$DESTDIR -lVSCommon
isEmpty(VS_CROSS):LIBS += -Wl,-rpath,$$LIBVSCOMMON_BUILDDIR/$$DESTDIR
