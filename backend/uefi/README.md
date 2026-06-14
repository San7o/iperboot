# UEFI

The standard PC boot interface.

[Specification](https://uefi.org/specifications).

## API

Calling conventions and datatypes (chapter 2.3):

- Functions follow C calling convention
- Pointers to the various global UEFI functions are found in the
  `EFI_RUNTIME_SERVICES` and `EFI_BOOT_SERVICES` tables that are located via the
  system table. Pointers to other functions defined in this specification are
  located dynamically through device handles.
- Pointers are passed as physical memory locations.
- Passing a structure larger than native width (4 bytes on supported 32-bit
  processors; 8 bytes on supported 64-bit processor instructions) on the stack
  will produce undefined results

CPU:

- x64 (chapter 2.3.4):
  - register `rcx`: `EFI_HANDLE`
  - register `rdx`: `EFI_SYSTEM_TABLE*`
  - register `rsp`
  - long mode (64 bit mode)
  - paging enabled and any memory space defined by the UEFI memory map is
    identity mapped
  - Interrupts are enabled but no interrupt services are supported
  - Direction flag in EFLAGs is clear, other general purpose registers are
    undefined.
  - 128KiB, or more, of available stack space, 16 bit aligned
  - `CR0.EM` must be zero
  - `CR0.TS` must be zero
- AArch64: TODO
