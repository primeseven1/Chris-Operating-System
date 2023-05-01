#pragma once

#include <stdint.h>
#include <stdarg.h>

// This frame is automatically pushed onto the stack by the CPU
struct exceptionCallFrame 
{
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t errorCode;
} __attribute__((packed));

// This frame gets pushed onto the stack by the syscall handler in ./trap_gates/syscall_handle.asm
struct syscallFrame
{
    uint32_t eax;
    uint32_t ebx;
    union
    {
        uint32_t value;
        va_list argList;
    } ecx;
    uint32_t edx;
} __attribute__((packed));