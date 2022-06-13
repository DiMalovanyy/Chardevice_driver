ifneq ($(KERNELRELEASE),)

# First compile Kbuild sources
include Kbuild

else

KDIR ?= /lib/modules/`uname -r`/build
PWD := $(CURDIR)

build:
	$(MAKE) -C $(KDIR) M=$$PWD modules 

install:
	$(MAKE) -C $(KDIR) M=$$PWD modules_install

clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean

endif
