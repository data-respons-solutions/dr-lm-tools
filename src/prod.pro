# The VitalSim2 setup
#include ( mkspecs/vitalsim2.pri )

#
# Top-level project file for the vs2-apps package.
# vs2-apps is the replacement for rootfs-lmas.
#
VS_BIN_PATH = $$(TARGET_BIN_PATH)
VS_LIB_PATH = $$(TARGET_LIB_PATH)
VS_CONF_PATH = $$(TARGET_CONF_PATH)
OUT_PWD =  $$(PWD)

TEMPLATE = subdirs
CONFIG  += ordered

SUBDIRS += libs IOC_Test IOC_Flash 
#WinmateTest qws_input eeprom_gen nvram

IOC_Test.depends = libs
IOC_Flash.depends = libs
nvram.depends = libs

target.path += $$(OUT_PWD)/opt/
INSTALLS += target
