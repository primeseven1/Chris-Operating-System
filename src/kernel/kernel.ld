SECTIONS
{
    ENTRY(kmain)

    /* This is the location the BIOS loads the kernel */
    . = 0x8000;
    .text :
    {
        *(.text)
    }

    .data :
    {
        *(.data)
    }

    .rodata :
    {
        *(.rodata)
    }

    .bss :
    {
        *(.bss)
    }
}