#include <kernel/kernel.h>
#include <kernel/kernel_modules/io/panic.h>

void kernelModeTrap(const char* caller, void* memoryAddress)
{
    struct panicInfo info = {
        .errorCode = UNEXPECTED_KERNEL_MODE_TRAP,
        .info = "There was a kernel mode trap, restart the system",
        .caller = caller,
        .memoryAddress = memoryAddress
    };

    kpanic(&info);
}