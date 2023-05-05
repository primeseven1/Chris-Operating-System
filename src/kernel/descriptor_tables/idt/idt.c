#include <kernel/kernel_modules/io/kprintf.h>
#include "../../interrupts/functions.h"
#include "./exception_gates.h"
#include "./idt.h"

static volatile struct
{
    uint16_t offsetLow;
    uint16_t segment;
    uint8_t alwaysZero;
    uint8_t typeAttributes;
    uint16_t offsetHigh;
} __attribute__((packed)) idt[256];

void IDTSetGate(uint8_t entry, uint32_t offset, segment_t segment, uint8_t typeAttributes)
{
    /*  offsetLow: The lower 16 bits
        offsetHigh: The higher 16 bits
        alwaysZero: This is reserved, and should always be set to zero
        typeAttributes: Specifies things like if it's a trap or interrupt, user level/kernel level, etc */
    idt[entry].offsetLow = offset & 0xFFFF;
    idt[entry].offsetHigh = (offset >> 16) & 0xFFFF;
    idt[entry].segment = (uint16_t)segment;
    idt[entry].alwaysZero = 0;
    idt[entry].typeAttributes = typeAttributes;
}

static void __attribute__((naked)) noHandle() { asm volatile("iret"); }

static inline void lidt()
{
    volatile struct
    {
        uint16_t limit;
        uint32_t base;
    } __attribute__((packed)) idtr = {
        .limit = sizeof(idt) - 1,
        .base = (uint32_t)&idt
    };

    asm volatile("lidt %0" : : "m"(idtr));
}

void initIDT()
{
    kprintf("\nInitializing IDT...\nSetting interrupt gates...");
    for (int i = 0; i < sizeof(idt) / sizeof(idt[0]); i++)
        IDTSetGate(
            i, 
            (uint32_t)noHandle, 
            GDT_ENTRY_KERNEL_CODE, 
            IDT_FLAG_INTERRUPT | GDT_ACCESS_RING0 );

    IDTSetExceptionGates();

    // Have to make sure that the syscall gate can be used by ring 3, as not doing so will cause a GPF
    IDTSetGate(
        IDT_SYSCALL, 
        (uint32_t)syscall_handle, 
        GDT_ENTRY_KERNEL_CODE, 
        IDT_FLAG_TRAP | GDT_ACCESS_RING3 );

    lidt();
    kprintf("\nIDT Initialized successfuly...");
}