#pragma once

#include <stdint.h>
#include <stdarg.h>

// Automatically pushed onto the stack by the CPU
struct exceptionContext
{
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t esp; 
    uint32_t ss;
} __attribute__((packed));

// This gets pushed onto the stack by the syscall handler in ./trap_gates/syscall_handle.asm
struct syscallRegisters
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