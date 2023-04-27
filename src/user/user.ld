SECTIONS
{
    ENTRY(umain)
    /* Where the kernel is located + the 16384 offset so that the kernel can jump to the user code */
    . = 0xc000;
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