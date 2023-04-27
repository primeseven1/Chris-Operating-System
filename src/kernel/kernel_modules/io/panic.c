#include <drivers/graphics/graphics.h>
#include <drivers/graphics/cursor.h>
#include <libc/stdlib.h>
#include <kernel/kernel.h>
#include <kernel/kernel_modules/io/panic.h>

void kpanic(const struct panicInfo* info)
{
    cli();
    disableCursor();
    clearScreen(VGA_LIGHT_BLUE);

    if (!info)
    {
        printString("Panic: Unknown information, parameter was NULL", VGA_WHITE, VGA_LIGHT_BLUE);
        for (;;);
    }

    char errorCode[33];
    itoa(info->errorCode, errorCode, 10);
    printString("Panic: ", VGA_WHITE, VGA_LIGHT_BLUE);
    printString(errorCode, VGA_WHITE, VGA_LIGHT_BLUE);

    printString("\nInfo: ", VGA_WHITE, VGA_LIGHT_BLUE);
    printString(info->info, VGA_WHITE, VGA_LIGHT_BLUE);

    char memoryAddress[33];
    printString("\nMemory address: ", VGA_WHITE, VGA_LIGHT_BLUE);
    printString("0x0", VGA_WHITE, VGA_LIGHT_BLUE);
    itoa((int)info->memoryAddress, memoryAddress, 16);
    printString(memoryAddress, VGA_WHITE, VGA_LIGHT_BLUE);

    printString("\nCaller: ", VGA_WHITE, VGA_LIGHT_BLUE);
    printString(info->caller, VGA_WHITE, VGA_LIGHT_BLUE);

    for (;;);
}