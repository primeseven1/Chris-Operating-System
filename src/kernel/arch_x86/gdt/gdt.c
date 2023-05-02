#include <kernel/kernel_modules/io/kprintf.h>
#include <kernel/kernel.h>
#include "./segments.h"
#include "./gdt.h"

static volatile struct
{
    uint16_t limitLow;
    uint16_t baseLow;
    uint8_t baseMiddle;
    uint8_t accessByte;
    uint8_t granularity;
    uint8_t baseHigh;
} __attribute__((packed)) gdt[6];

void GDTSetEntry(segment_t segment, uint16_t limitLow, uint32_t base, uint8_t accessByte, uint8_t granularity)
{
    // Divided by the size of a GDT entry to get the actual index in the array

    /*  limitLow: Segment limit
        baseLow: lower 16 bits
        baseMiddle: Middle 8 bits
        accessByte: Contains things like privilage level, whether it's present, etc
        granularity:  Used to measure the segment limit */
    gdt[segment / sizeof(gdt[0])].limitLow = limitLow;
    gdt[segment / sizeof(gdt[0])].baseLow = base & 0xFFFF;
    gdt[segment / sizeof(gdt[0])].baseMiddle = (base >> 16) & 0xFF;
    gdt[segment / sizeof(gdt[0])].accessByte = accessByte;
    gdt[segment / sizeof(gdt[0])].granularity = granularity;
    gdt[segment / sizeof(gdt[0])].baseHigh = (base >> 24) & 0xFF;
}

extern void __attribute__((ASM_LINKAGE)) set_kernel_segment_registers();

static inline void lgdt()
{
    volatile struct
    {
        uint16_t limit;
        uint32_t base;
    } __attribute__((packed)) gdtr = {
        .limit = sizeof(gdt) - 1,
        .base = (uint32_t)&gdt
    };

    asm volatile("lgdt %0" : : "m"(gdtr));
    set_kernel_segment_registers();
}

void initGDT()
{
    kprintf("\nInitializing GDT...");
    GDTSetGeneralSegments();
    GDTSetTSSSegment();
    kprintf("\nGDT segments initialized successfuly...");
    
    lgdt();
    loadTSS();
    kprintf("\nTSS loaded successfuly...\nGDT initalized successfuly...");
}