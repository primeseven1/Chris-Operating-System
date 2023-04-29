#include <drivers/graphics/cursor.h>
#include <drivers/graphics/graphics.h>
#include <kernel/kernel_modules/io/kprintf.h>
#include <kernel/kernel.h>
#include "../hal/hal.h"

void kmain()
{
    initHAL();
    sti();
    disableCursor();

    kprintf("Switching to user mode...");
    clearScreen(VGA_BLACK);
}