#include <kernel/kernel_modules/io/kprintf.h>
#include <libc/string.h>
#include <libc/stdlib.h>
#include <stdarg.h>

static vgaColor_t fgColor = VGA_WHITE;
static vgaColor_t bgColor = VGA_BLACK;

void setFgColor(vgaColor_t color) { fgColor = color; }

void setBgColor(vgaColor_t color) { bgColor = color; }

void vkprintf(const char* format, va_list args)
{
    if (!format)
        return;

    int length = strlen(format);
    for (int i = 0; i < length; i++) 
    {
        if (format[i] != '%')
        {
            printChar(format[i], fgColor, bgColor);
            continue;
        }

        switch (format[++i])
        {
            case 'c':
                printChar((char)va_arg(args, int), fgColor, bgColor);
                break;
            
            case 's':
            {
                const char* ptr = (const char*)va_arg(args, char*);
                if (!ptr)
                    break;

                printString(ptr, fgColor, bgColor);
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
                printString(buffer, fgColor, bgColor);
                break;
            }
            
            case 'f':
            {
                char buffer[64];
                memset(buffer, 0, sizeof(buffer));
                ftoa((float)va_arg(args, double), buffer, 5);
                printString(buffer, fgColor, bgColor);
                break;
            }

            case 'p':
            {
                char buffer[33];
                memset(buffer, 0, sizeof(buffer));

                // Just converting the pointer to base 16
                itoa((int)va_arg(args, void*), buffer, 16);
                printString("0x", fgColor, bgColor);
                printString(buffer, fgColor, bgColor);
                break;
            }
            
            default:
                printChar(format[i], fgColor, bgColor);
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