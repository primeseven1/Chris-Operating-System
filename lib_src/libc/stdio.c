#include <stdint.h>
#include <libc/stdio.h>
#include <stdarg.h>

void clrscr(vgaColor_t color)
{
    uint32_t u32color = (uint32_t)color;

    /* eax 0x01: output system call
       ebx: color 
       edx 0x01: the */
    asm volatile("mov $0x01, %eax");
    asm volatile("mov %0, %%ebx" : : "m"(u32color));
    asm volatile("mov $0x01, %edx");
    asm volatile("int $0x80");
}

void printf(const char* format, ...)
{
    if (!format)
        return;

    va_list argList;
    va_start(argList, format);

    /* eax 0x01: The output system call
       ebx: Format
       ecx: The variable arguments list */
    asm volatile("mov $0x01, %eax");
    asm volatile("mov %0, %%ebx" : : "m"(format));
    asm volatile("mov %0, %%ecx" : : "m"(argList));
    asm volatile("mov $0x02, %edx");
    asm volatile("int $0x80");

    va_end(argList);
}

void cursorDisable()
{
    /* eax 0x01: output system call
       edx 0x03: Disable cursor */
    asm volatile("mov $0x01, %eax");
    asm volatile("mov $0x03, %edx");
    asm volatile("int $0x80");
}

void cursorEnable(uint32_t cursorStart, uint32_t cursorEnd)
{
    // ebx and ecx are more like the thickness of the cursor
    /* eax 0x01: output system call 
       ebx: Start of the cursor
       ecx: End of the cursor */
    asm volatile("mov $0x01, %eax");
    asm volatile("mov %0, %%ebx" : : "m"(cursorStart));
    asm volatile("mov %0, %%ecx" : : "m"(cursorEnd));
    asm volatile("mov $0x04, %edx");
    asm volatile("int $0x80");
}

void moveCursor(uint32_t x, uint32_t y)
{
    /* eax 0x01: The output system call
       ebx: line number-1 basically
       ecx: where on the line-1 pretty much 
       edx 0x05: Move cursor */
    asm volatile("mov $0x01, %eax");
    asm volatile("mov %0, %%ebx" : : "m"(x));
    asm volatile("mov %0, %%ecx" : : "m"(y));
    asm volatile("mov $0x05, %edx");
    asm volatile("int $0x80");
}

char getChar()
{
    uint32_t character;

    /* eax 0x02: The input system call
       edx 0x01: Get character */
    asm volatile("mov $0x02, %eax");
    asm volatile("mov $0x01, %edx");
    asm volatile("int $0x80");
    asm volatile("mov %%eax, %0" : "=r"(character));

    return (char)character;
}