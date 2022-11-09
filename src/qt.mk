
export INSTALL_ROOT ?= $(PWD)/../prod_build
export TARGET_CONF_PATH=/usr/local/conf
export TARGET_BIN_PATH=/home/octavio/Laerdal/simpad_new_repos/dr-lm-tools/opt
export TARGET_LIB_PATH=/home/octavio/Laerdal/simpad_new_repos/dr-lm-tools/usr/lib
export TARGET_LODTEST_PATH=$(INSTALL_ROOT)/usr/share/dr-prodtest/LodTest
export TARGET_CONFIG_PATH=$(INSTALL_ROOT)/usr/share/dr-prodtest
export TARGET_QT_PATH=/opt/qt-embedded
export CROSS_COMPILE=arm-linux-gnueabi-

qt:
	/opt/qt-embedded/bin/qmake prod.pro -recursive

install_all:
	make  install
	install -m0755 -D LodTest/blue.sh $(TARGET_LODTEST_PATH)/blue.sh
	install -m0755 -D LodTest/blueoff.sh $(TARGET_LODTEST_PATH)/blueoff.sh
	install -m0755 -D LodTest/red.sh $(TARGET_LODTEST_PATH)/red.sh
	install -m0644 -D LodTest/login_file $(TARGET_LODTEST_PATH)/login_file
	install -m0644 -D LodTest/login_file_self $(TARGET_LODTEST_PATH)/login_file_self
	install -m0644 -D config/bu-asound.state  $(TARGET_CONFIG_PATH)/bu-asound.state
	install -m0644 -D config/rc-asound.state  $(TARGET_CONFIG_PATH)/rc-asound.state
