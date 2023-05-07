#include <stdint.h>
#include <libc/stdio.h>
#include <stdarg.h>
#include <kernel/syscalls/syscalls.h>

/* eax: The system call type, but is also used for return values after the system call
   ebx: parameter 1
   ecx: parameter 2
   edx: The eax selector */

void clrscr(vgaColor_t color)
{
    /* The reason for this is to guaruntee 4 bytes being moved
       This is to avoid the issues of leftover higher bits in the register */
    uint32_t u32color = (uint32_t)color;

    asm volatile("movl %0, %%eax" : : "i"(SYS_OUT));
    asm volatile("movl %0, %%ebx" : : "m"(u32color));
    asm volatile("movl %0, %%edx" : : "i"(CLEAR_SCREEN));
    asm volatile("int $0x80");
}

void printf(const char* format, ...)
{
    if (!format)
        return;

    va_list argList;
    va_start(argList, format);

    asm volatile("movl %0, %%eax" : : "i"(SYS_OUT));
    asm volatile("movl %0, %%ebx" : : "m"(format));
    asm volatile("movl %0, %%ecx" : : "m"(argList));
    asm volatile("movl %0, %%edx" : : "i"(PRINTF));
    asm volatile("int $0x80");

    va_end(argList);
}

void changeFgColor(vgaColor_t color)
{
    uint32_t u32color = (uint32_t)color;

    asm volatile("movl %0, %%eax" : : "i"(SYS_OUT));
    asm volatile("movl %0, %%ebx" : : "m"(u32color));
    asm volatile("movl %0, %%edx" : : "i"(CHANGE_FG_COLOR));
    asm volatile("int $0x80");
}

void changeBgColor(vgaColor_t color)
{
    uint32_t u32color = (uint32_t)color;

    asm volatile("movl %0, %%eax" : : "i"(SYS_OUT));
    asm volatile("movl %0, %%ebx" : : "m"(u32color));
    asm volatile("movl %0, %%edx" : : "i"(CHANGE_BG_COLOR));
    asm volatile("int $0x80");
}

void cursorDisable()
{
    asm volatile("movl %0, %%eax" : : "i"(SYS_OUT));
    asm volatile("movl %0, %%edx" : : "i"(CURSOR_DISABLE));
    asm volatile("int $0x80");
}

void cursorEnable(uint32_t cursorStart, uint32_t cursorEnd)
{
    asm volatile("movl %0, %%eax" : : "i"(SYS_OUT));
    asm volatile("movl %0, %%ebx" : : "m"(cursorStart));
    asm volatile("movl %0, %%ecx" : : "m"(cursorEnd));
    asm volatile("movl %0, %%edx" : : "i"(CURSOR_ENABLE));
    asm volatile("int $0x80");
}

void moveCursor(uint32_t x, uint32_t y)
{
    asm volatile("movl %0, %%eax" : : "i"(SYS_OUT));
    asm volatile("movl %0, %%ebx" : : "m"(x));
    asm volatile("movl %0, %%ecx" : : "m"(y));
    asm volatile("movl %0, %%edx" : : "i"(CURSOR_UPDATE));
    asm volatile("int $0x80");
}

char getChar()
{
    uint32_t character;

    asm volatile("movl %0, %%eax" : : "i"(SYS_IN));
    asm volatile("movl %0, %%edx" : : "i"(GET_KEY_CHAR));
    asm volatile("int $0x80");
    asm volatile("movl %%eax, %0" : "=r"(character));

    return (char)character;
}