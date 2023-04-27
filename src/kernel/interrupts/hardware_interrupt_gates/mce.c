#include <kernel/kernel_modules/io/panic.h>
#include <kernel/kernel.h>
#include "../functions.h"

void __attribute__((HW_INTERRUPT)) mce(const struct exceptionCallFrame* frame)
{
    cli();

    struct panicInfo info = {
        .errorCode = CPU_EXCEPTION,
        .info = "A machine check exception occurred",
        .caller = __func__,
        .memoryAddress = (void*)frame->eip
    };

    kpanic(&info);
}