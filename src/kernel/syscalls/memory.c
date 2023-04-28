#include "./syscalls.h"
#include "../kernel_modules/memory/heap.h"

void* sysMalloc(const struct syscallFrame* frame)
{
    // ebx is the block size
    void* ptr = kmalloc((size_t)frame->ebx);
    return ptr;
}

void sysFree(const struct syscallFrame* frame)
{
    // ebx is the pointer that needs to be freed
    kfree((void*)frame->ebx);
}