BACKEND_OBJ     += backend/uefi/uefi_main.o

# Set arch for EDK include dir
ifeq (${ARCH},x86_64)
  EDK2_ARCH = X64
else
  EDK2_ARCH = unknown
endif

BACKEND_CFLAGS += -target ${ARCH}-unknown-windows \
    -ffreestanding \
    -fshort-wchar \
    -I backend/uefi/include -I backend/uefi/include/${EDK2_ARCH}
BACKEND_LDFLAGS += -target ${ARCH}-unknown-windows \
    -nostdlib \
    -Wl,-entry:efi_main \
    -Wl,-subsystem:efi_application \
    -fuse-ld=lld-link

# Image

MKGPT_DIR       ?= external/mkgpt
MKGPT_BIN       ?= ${MKGPT_DIR}/mkgpt
EFI_BIN         ?= BOOT${EDK2_ARCH}.EFI
FAT_IMG         ?= fat.img
HD_IMG          ?= hdimage.bin
IPERBOOT_IMG     = ${HD_IMG}

DIST_OBJ        += ${EFI_BIN} ${FAT_IMG} ${HD_IMG} ${MKGPT_BIN}

${MKGPT_DIR}/mkgpt:
	cd ${MKGPT_DIR} && autoreconf -f -i && ./configure && make

${EFI_BIN}: ${BACKEND_OUT}
	cp ${BACKEND_OUT} ${EFI_BIN}

${FAT_IMG}: ${EFI_BIN}
	dd if=/dev/zero of=${FAT_IMG} bs=1k count=1440
	mformat -i ${FAT_IMG} -f 1440 ::
	mmd -i ${FAT_IMG} ::/EFI
	mmd -i ${FAT_IMG} ::/EFI/BOOT
	mcopy -i ${FAT_IMG} ${EFI_BIN} ::/EFI/BOOT

${HD_IMG}: ${MKGPT_BIN} ${FAT_IMG}
	${MKGPT_BIN} -o ${HD_IMG} --image-size 4096 --part ${FAT_IMG} --type system

# Runtime

OVMF_DIR ?= /usr/share/OVMF

QEMU_FLAGS = -M q35 \
    -hda ${HD_IMG} \
    -drive if=pflash,format=raw,readonly=on,file=${OVMF_DIR}/OVMF_CODE.fd \
    -drive if=pflash,format=raw,file=${OVMF_DIR}/OVMF_VARS.fd

.PHONY: qemu
qemu: ${HD_IMG} ## Run image with qemu
	qemu-system-${ARCH} ${QEMU_FLAGS}
