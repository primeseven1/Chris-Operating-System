#include <kernel/kernel_modules/io/panic.h>
#include <kernel/kernel.h>
#include "../../descriptor_tables/gdt/gdt.h"
#include "../functions.h"

void __attribute__((TRAP)) invalidOpcode(const struct exceptionContext* context)
{
    cli();

    // This is checking if the code segment was the kernel code segment, if it is, the system crashes
    if (context->cs == GDT_ENTRY_KERNEL_CODE)
        kernelModeTrap(__func__, (void*)context->eip);

    // For now
    struct panicInfo info = {
        .errorCode = CPU_EXCEPTION,
        .info = "An invalid opcode exception occurred, the program will be terminated",
        .caller = __func__,
        .memoryAddress = (void*)context->eip
    };

    kpanic(&info);
}