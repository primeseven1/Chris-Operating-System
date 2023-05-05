#include <kernel/kernel_modules/io/panic.h>
#include <kernel/kernel.h>
#include "../../descriptor_tables/gdt/gdt.h"
#include "../functions.h"

void __attribute__((TRAP)) divideByZero(const struct exceptionCallFrame* frame)
{
    cli();

    // This is checking if the code segment was the kernel code segment, if it is, the system crashes
    if (frame->cs == GDT_ENTRY_KERNEL_CODE)
        kernelModeTrap(__func__, (void*)frame->eip);

    // Doing this for now, preferably want to terminate the program that had the fault
    struct panicInfo info = {
        .errorCode = CPU_EXCEPTION,
        .info = "A divide by zero exception occurred, the program will be terminated",
        .caller = __func__,
        .memoryAddress = (void*)frame->eip
    };

    kpanic(&info);
}