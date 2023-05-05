#include "../../interrupts/functions.h"
#include "./idt.h"

void IDTSetExceptionGates()
{
    // Even if the kernel is in user level, it will still be able to access these
    IDTSetGate(
        IDT_DIVIDE_BY_ZERO_EXCEPTION,
        (uint32_t)divideByZero, 
        GDT_ENTRY_KERNEL_CODE, 
        IDT_FLAG_TRAP | GDT_ACCESS_RING0 );

    IDTSetGate(
        IDT_GENERAL_PROTECTION_FAULT_EXCEPTION,
        (uint32_t)gpf, 
        GDT_ENTRY_KERNEL_CODE, 
        IDT_FLAG_TRAP | GDT_ACCESS_RING0 );

    IDTSetGate(
        IDT_MACHINE_CHECK_EXCEPTION,
        (uint32_t)mce,
        GDT_ENTRY_KERNEL_CODE,
        IDT_FLAG_INTERRUPT | GDT_ACCESS_RING0 );

    IDTSetGate(
        IDT_INVALID_OPCODE_EXCEPTION,
        (uint32_t)invalidOpcode,
        GDT_ENTRY_KERNEL_CODE,
        IDT_FLAG_TRAP | GDT_ACCESS_RING0 );
}