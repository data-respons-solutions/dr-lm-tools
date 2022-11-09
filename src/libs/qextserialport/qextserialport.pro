# The VitalSim2 setup
#include ( ../../mkspecs/vitalsim2.pri )
include ( ../../prod.pri )
#
TEMPLATE = subdirs
CONFIG   += ordered
SUBDIRS  = src

# VS2 remove
#           examples/enumerator \
#           examples/event
