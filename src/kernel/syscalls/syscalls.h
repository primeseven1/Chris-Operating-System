#pragma once

#include <kernel/kernel.h>
#include <drivers/graphics/graphics.h>
#include <drivers/graphics/cursor.h>
#include <drivers/graphics/graphics.h>
#include <kernel/kernel_modules/io/kprintf.h>
#include <stdint.h>

enum syscallTable
{
    SYS_OUT = 1,
    SYS_IN,
    SYS_MALLOC,
    SYS_FREE
};

enum edxSyscallValues
{
    // SYS_OUT
    CLEAR_SCREEN = 1,
    PRINTF,
    CURSOR_DISABLE,
    CURSOR_ENABLE,
    CURSOR_UPDATE,

    // SYS_IN
    GET_KEY_CHAR = 1

    // SYS_MALLOC and SYS_FREE do not use edx
};

#define NUM_OF_SYSCALLS 4

void sysOut(const struct syscallFrame* frame);
int32_t sysIn(const struct syscallFrame* frame);
void* sysMalloc(const struct syscallFrame* frame);
void sysFree(const struct syscallFrame* frame);

void badSyscall(const char* caller);