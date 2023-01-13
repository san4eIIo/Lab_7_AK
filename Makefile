

ccflags-y +=-g
# normal makefile
KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD

	$(CROSS_COMPILE)strip -g hello.ko
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
