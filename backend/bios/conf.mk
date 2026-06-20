BACKEND_OBJ += backend/bios/boot.o

BACKEND_LDFLAGS += -T backend/bios/linker.ld \
    -target ${ARCH}-unknown-none -nostdlib -static

ASFLAGS += -f elf64 -i backend/bios/

# Image

BACKEND_OUT  = backend/bios/bios.img
IPERBOOT_IMG = ${BACKEND_OUT}
DIST_OBJ += ${IPERBOOT_IMG}

${IPERBOOT_IMG}: ${BACKEND_OUT}
	cp ${BACKEND_OUT} ${IPERBOOT_IMG}

# Runtime

QEMU_FLAGS = -drive format=raw,file=${IPERBOOT_IMG},if=ide \
    -serial stdio

.PHONY: qemu
qemu: ${IPERBOOT_IMG}
	${QEMU} ${QEMU_FLAGS}

