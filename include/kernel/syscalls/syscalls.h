#pragma once

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
    CHANGE_FG_COLOR,
    CHANGE_BG_COLOR,
    CURSOR_DISABLE,
    CURSOR_ENABLE,
    CURSOR_UPDATE,

    // SYS_IN
    GET_KEY_CHAR = 1

    // SYS_MALLOC and SYS_FREE do not use edx
};

#ifdef RING0

#include <stdint.h>
#include "../../../src/kernel/interrupts/contexts.h"

#define NUM_OF_SYSCALLS 4

void sysOut(const struct syscallRegisters* registers);
int32_t sysIn(const struct syscallRegisters* registers);
void* sysMalloc(const struct syscallRegisters* registers);
void sysFree(const struct syscallRegisters* registers);

void badSyscall(const char* caller);

#endif // RING0