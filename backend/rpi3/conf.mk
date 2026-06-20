ARCH = aarch64

BACKEND_OBJ += backend/rpi3/start.o \
    backend/rpi3/rpi3_main.o

include backend/rpi3/drivers/conf.mk
include backend/rpi3/kernel/conf.mk

AS = clang
LD = ld.lld

BACKEND_CFLAGS  += --target=aarch64-elf \
    -nostdlib \
    -mcpu=cortex-a53+nosimd \
    -I backend/rpi3/include
BACKEND_ASFLAGS += --target=aarch64-elf \
    -nostdlib \
    -mcpu=cortex-a53+nosimd -c
BACKEND_LDFLAGS += -T backend/rpi3/link.ld \
    -nostdlib

# Image

BACKEND_OUT  = backend/rpi3/kernel8.elf
IPERBOOT_IMG = backend/rpi3/kernel8.img
DIST_OBJ     += ${BACKEND_OUT} ${IPERBOOT_IMG}

${IPERBOOT_IMG}: ${BACKEND_OUT}
	llvm-objcopy -O binary ${BACKEND_OUT} ${IPERBOOT_IMG}

# Booting

QEMU_FLAGS = -M raspi3b \
             -cpu cortex-a53 \
             -kernel ${IPERBOOT_IMG} \
             -serial stdio

.PHONY: qemu
qemu: ${IPERBOOT_IMG} ## Run image with qemu
	${QEMU} ${QEMU_FLAGS}
