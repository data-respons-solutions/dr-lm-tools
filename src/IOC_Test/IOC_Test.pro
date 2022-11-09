TEMPLATE = subdirs
CONFIG  += ordered
include ( ../prod.pri )
SUBDIRS = \
	common \
	ioctest \
    pso \
    pulsedriver \
	gpiotopower \
#	productiontest \
	cufftest 

ioctest.depends = common
pso.depends = common
pulsedriver.depends = common
gpiotopower.depends = common
#productiontest.depends = common
cufftest.depends = common
