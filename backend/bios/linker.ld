OUTPUT_FORMAT("binary")
ENTRY("bios_entry")

SECTIONS
{
    . = 0x7C00;

    .text : {
        *(.boot_text)
        *(.text)


        . = 0x7DFE;
        SHORT(0xAA55);
    }

    .rodata : { *(.rodata) }
    .data   : { *(.data) }
    .bss    : { *(.bss) }

}
