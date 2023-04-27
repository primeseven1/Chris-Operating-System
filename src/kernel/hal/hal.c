#include <drivers/graphics/graphics.h>
#include "../kernel_modules/memory/heap.h"
#include <kernel/kernel_modules/io/kprintf.h>
#include "../arch_x86/gdt/gdt.h"
#include "../arch_x86/idt/idt.h"
#include "./hal.h"

void initHAL()
{
    // None of the text based graphics will work without initializing this first :D
    initGraphicsDriver();
    initHeap();
    kprintf("Initializing HAL...");
    initGDT();
    initIDT();
    kprintf("\nHAL initialized successfuly...");
}