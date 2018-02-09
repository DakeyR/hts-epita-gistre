
KDIR ?= ${KBUILD_OUTPUT} # /usr/lib/modules/$(shell uname -r)/build

obj-m := kprobe-open.o

all: modules

modules modules_install clean help:
	$(MAKE) -C $(KDIR) M=$(PWD) $@
