#include <drivers/graphics/cursor.h>
#include <drivers/graphics/graphics.h>
#include <kernel/kernel_modules/io/kprintf.h>
#include <kernel/kernel.h>
#include <kernel/kernel_modules/io/input.h>
#include "../hal/hal.h"

void kmain()
{
    initHAL();
    sti();

    kprintf("Switching to user mode...");

    // Before going into user mode, clear the screen and bring the cursor (not the vga cursor) down a line
    clearScreen(VGA_BLACK);
    printString("Work in progress\n", VGA_RED, VGA_DARK_GREY);
    disableCursor();
}