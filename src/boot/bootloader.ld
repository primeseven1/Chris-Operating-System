ENTRY(_start)

SECTIONS
{
    /* BIOS loads the bootloader at this location, so the offset has to be set to this */
    . = 0x7c00;

    .text :
    {
        *(.text)
    }

    .data :
    {
        *(.data)
    }
}