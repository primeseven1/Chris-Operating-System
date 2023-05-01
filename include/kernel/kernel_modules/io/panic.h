#pragma once

#ifndef RING0
#warning "Only ring 0 needs panic.h"
#endif // RING0

#ifdef RING0

enum errorCodes
{
    CPU_EXCEPTION,
    UNEXPECTED_KERNEL_MODE_TRAP,
    KERNEL_HEAP_ERROR,
    BAD_SYSCALL
};

struct panicInfo
{
    unsigned int errorCode;
    const char* info;
    const char* caller;
    void* memoryAddress;
};

void kpanic(const struct panicInfo* info);

#endif // RING0