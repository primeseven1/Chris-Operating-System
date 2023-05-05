#include <drivers/graphics/graphics.h>
#include <kernel/kernel_modules/memory/heap.h>
#include <kernel/kernel_modules/io/kprintf.h>
#include "../descriptor_tables/gdt/gdt.h"
#include "../descriptor_tables/idt/idt.h"
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