#include <kernel/kernel.h>
#include "../callFrames.h"
#include "../functions.h"
#include "../../syscalls/syscalls.h"

anyType_t __attribute__((ASM_LINKAGE)) check_syscall(const struct syscallFrame frame)
{
    if (frame.eax < 1 || frame.eax > NUM_OF_SYSCALLS)
        badSyscall(__func__);

    // eax will hold return values, since it's an anytype return type (anytype is just a typedef for void)
    switch (frame.eax)
    {
        case SYS_OUT:
            sysOut(&frame);
            break;

        case SYS_IN:
        {
            uint32_t value = sysIn(&frame);
            asm volatile("mov %0, %%eax" : : "m"(value));
            break;
        }

        case SYS_MALLOC:
        {
            void* ptr = sysMalloc(&frame); 
            asm volatile("mov %0, %%eax" : : "m"(ptr));
            break;
        }

        case SYS_FREE:
            sysFree(&frame);
            break;
    }
}