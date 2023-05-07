#include <kernel/syscalls/syscalls.h>
#include <kernel/kernel_modules/memory/heap.h>

void* sysMalloc(const struct syscallRegisters* registers)
{
    // ebx is the block size
    void* ptr = kmalloc((size_t)registers->ebx);
    return ptr;
}

void sysFree(const struct syscallRegisters* registers)
{
    // ebx is the pointer that needs to be freed
    kfree((void*)registers->ebx);
}