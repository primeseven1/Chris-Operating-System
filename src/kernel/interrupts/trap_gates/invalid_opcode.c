#include <kernel/kernel_modules/io/panic.h>
#include <kernel/kernel.h>
#include "../../arch_x86/gdt/gdt.h"
#include "../functions.h"

void __attribute__((TRAP)) invalidOpcode(const struct exceptionCallFrame* frame)
{
    cli();

    // This is checking if the code segment was the kernel code segment, if it is, the system crashes
    if (frame->cs == GDT_ENTRY_KERNEL_CODE)
        kernelModeTrap(__func__, (void*)frame->eip);

    // For now
    struct panicInfo info = {
        .errorCode = CPU_EXCEPTION,
        .info = "An invalid opcode exception occurred, the program will be terminated",
        .caller = __func__,
        .memoryAddress = (void*)frame->eip
    };

    kpanic(&info);
}