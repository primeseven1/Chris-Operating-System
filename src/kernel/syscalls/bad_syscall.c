#include <kernel/kernel_modules/io/panic.h>
#include <stddef.h>

void badSyscall(const char* caller)
{
    struct panicInfo info = {
        .errorCode = BAD_SYSCALL,
        .info = "A bad syscall exception occurred",
        .caller = caller,
        .memoryAddress = NULL
    }; 

    kpanic(&info);
}