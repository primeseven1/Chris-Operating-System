#pragma once

#include <stdint.h>
#include <stdarg.h>

struct exceptionCallFrame 
{
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t errorCode;
} __attribute__((packed));

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