# BIOS

The BIOS (Basic Input and Output) is the legacy way of booting a PC. It was
originally the firmware of the IBM PC, which became the de-facto standard and
lowest common denominator among all following PCs. Despite being the main way to
boot a PC, the BIOS does not have a standard interface, meaning that many
implementations had some differences which are annoying to work with.

## API

CPU:

- Only x86 architecture
- Single core
- CPU is in 16 bits mode, aka "Real Mode"
- no segmentation, no paging enabled

Registers:

- `dl` contains the ID of the bootdrive
- all other registers have undefined values, including base pointer, stack
  pointer and segment registers

Memory:

- the first sector (512 bits) of the program is loaded at address 0x7C00
- the memory map can be queried

The first 1MB of memory is mapped like this:

|-------------------------|---------|----------------------------------|
| Address Range (Hex)     | Size    | Description                      |
|-------------------------|---------|----------------------------------|
| 0x000F0000 - 0x000FFFFF | 64 KiB  | Motherboard BIOS                 |
| 0x000C8000 - 0x000EFFFF | 160 KiB | BIOS Expansions (Typically)      |
| 0x000C0000 - 0x000C7FFF | 32 KiB  | Video BIOS                       |
| 0x000A0000 - 0x000BFFFF | 128 KiB | Video Display Memory (Hardware)  |
|-------------------------|---------|----------------------------------|
| 0x00080000 - 0x0009FFFF | 128 KiB | EBDA (Extended BIOS Data Area)   |
| 0x00007E00 - 0x0007FFFF | 480.5 K | Conventional Memory              |
| 0x00007C00 - 0x00007DFF | 512 B   | Your OS BootSector               |
| 0x00000500 - 0x00007BFF | 29.75 K | Conventional Memory              |
| 0x00000400 - 0x000004FF | 256 B   | BDA (BIOS Data Area)             |
| 0x00000000 - 0x000003FF | 1 KiB   | Real Mode IVT (Interrupt Vector) |
|-------------------------|---------|----------------------------------|

You can invoke BIOS functionalities via interrupts, they are unofficially
documented in the great [Ralf Brown's Interrupt
List](https://www.ctyme.com/rbrown.htm).

The BIOS boot sequence for x86_64 looks like this:

- CPU starts executing in 16-bit real mode, with BIOS access, at address 0x7C00
- Use the bios to load the rest of the bootloader
- Setup and load the GDT with a flat memory layout
- Go to protected mode
- Enable A20 line
- Setup GDT again
- Setup the page table
- Enable long mode
- Call the kernel main function
