#include <kernel/kernel_modules/io/kprintf.h>
#include <drivers/graphics/graphics.h>
#include <libc/string.h>
#include <libc/stdlib.h>
#include <stdarg.h>

void vkprintf(const char* format, va_list args)
{
    if (!format)
        return;

    int length = strlen(format);
    for (int i = 0; i < length; i++) 
    {
        if (format[i] != '%')
        {
            printChar(format[i], VGA_WHITE, VGA_BLACK);
            continue;
        }

        switch (format[++i])
        {
            case 'c':
                printChar((char)va_arg(args, int), VGA_WHITE, VGA_BLACK);
                break;
            
            case 's':
            {
                const char* ptr = (const char*)va_arg(args, char*);
                if (!ptr)
                    break;

                printString(ptr, VGA_WHITE, VGA_BLACK);
                break;
            }
            
            /* For these conversions, using a memset on the buffers prevents leftover values from previous function calls
               I don't know why that happens, i've tested the conversion functions, and the memset ended up working */
            case 'd':
            case 'i':
            {
                char buffer[33];
                memset(buffer, 0, sizeof(buffer));
                itoa(va_arg(args, int), buffer, 10);
                printString(buffer, VGA_WHITE, VGA_BLACK);
                break;
            }
            
            case 'f':
            {
                char buffer[64];
                memset(buffer, 0, sizeof(buffer));
                ftoa((float)va_arg(args, double), buffer, 5);
                printString(buffer, VGA_WHITE, VGA_BLACK);
                break;
            }

            case 'p':
            {
                char buffer[33];
                memset(buffer, 0, sizeof(buffer));

                // Just converting the pointer to base 16
                itoa((int)va_arg(args, void*), buffer, 16);
                printString("0x", VGA_WHITE, VGA_BLACK);
                printString(buffer, VGA_WHITE, VGA_BLACK);
                break;
            }
            
            default:
                printChar(format[i], VGA_WHITE, VGA_BLACK);
                break;
        }
    }
}

void kprintf(const char* format, ...)
{
    if (!format)
        return;

    va_list argList;
    va_start(argList, format);

    vkprintf(format, argList);

    va_end(argList);
}