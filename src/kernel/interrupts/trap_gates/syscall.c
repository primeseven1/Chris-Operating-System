#include <kernel/kernel.h>
#include "../contexts.h"
#include "../functions.h"
#include <kernel/syscalls/syscalls.h>

anyType_t __attribute__((ASM_LINKAGE)) check_syscall(const struct syscallRegisters registers)
{
    switch (registers.eax)
    {
        case SYS_OUT:
            sysOut(&registers);
            break;

        case SYS_IN:
        {
            uint32_t value = sysIn(&registers);
            asm volatile("mov %0, %%eax" : : "m"(value));
            break;
        }

        case SYS_MALLOC:
        {
            void* ptr = sysMalloc(&registers); 
            asm volatile("mov %0, %%eax" : : "m"(ptr));
            break;
        }

        case SYS_FREE:
            sysFree(&registers);
            break;

        default:
            badSyscall(__func__);
            break;
    }
}