BACKEND_OBJ += backend/bios/boot.o

BACKEND_CFLAGS  += -target ${ARCH}-unknown-none
BACKEND_LDFLAGS += -T backend/bios/link.ld \
    -nostdlib \
    -static
BACKEND_ASFLAGS += -f elf64 -i backend/bios/

# Image

BACKEND_OUT  = backend/bios/bios.img
IPERBOOT_IMG = ${BACKEND_OUT}
DIST_OBJ += ${IPERBOOT_IMG}

# Booting

QEMU_FLAGS = -serial stdio \
    -drive format=raw,file=${IPERBOOT_IMG},if=ide

.PHONY: qemu
qemu: ${IPERBOOT_IMG} ## Run image with qemu
	${QEMU} ${QEMU_FLAGS}

