

# To support cross-compiling for kernel modules:
# For architecture (cpu) 'arch', invoke make as:
#  make ARCH=<arch> CROSS_COMPILE=<cross-compiler-prefix>

ifeq ($(ARCH),mips)
  # *UPDATE* 'KDIR' below to point to the ARM Linux kernel source tree on your box
  KDIR ?= /home/linuxdev/openwrt/build_dir/target-mipsel_74kc_musl/linux-bcm47xx_mips74k/linux-5.4.143

else
  # 'KDIR' is the Linux 'kernel headers' package on your host system
  KDIR ?= /lib/modules/$(shell uname -r)/build
endif

# Set FNAME_C to the kernel module name source filename (without .c)
FNAME_C := hello

PWD            := $(shell pwd)
obj-m          += ${FNAME_C}.o
EXTRA_CFLAGS   += -DDEBUG

all:
	@echo
	@echo '--- Building : KDIR=${KDIR} ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} EXTRA_CFLAGS=${EXTRA_CFLAGS} ---'
	@echo
	make -C $(KDIR) M=$(PWD) modules
install:
	@echo
	@echo "--- installing ---"
	@echo " [First, invoke the 'make' ]"
	make
	@echo
	@echo " [Now for the 'sudo make install' ]"
	sudo make -C $(KDIR) M=$(PWD) modules_install
	sudo depmod
clean:
	@echo
	@echo "--- cleaning ---"
	@echo
	make -C $(KDIR) M=$(PWD) clean
	rm -f *~   # from 'indent'
