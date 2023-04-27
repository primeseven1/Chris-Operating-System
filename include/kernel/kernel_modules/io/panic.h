#pragma once

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