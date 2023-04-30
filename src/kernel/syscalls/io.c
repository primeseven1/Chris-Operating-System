#include <drivers/graphics/graphics.h>
#include <drivers/graphics/cursor.h>
#include <kernel/kernel.h>
#include <kernel/kernel_modules/io/kprintf.h>
#include <kernel/kernel_modules/io/input.h>
#include "../interrupts/callFrames.h"
#include "syscalls.h"

void sysOut(const struct syscallFrame* frame)
{
    switch (frame->edx)
    {
        case CLEAR_SCREEN:
            // ebx: color
            clearScreen((vgaColor_t)frame->ebx);
            break;
        
        case PRINTF:
            /* ebx: format 
               ecx: the arg list */
            vkprintf((const char*)frame->ebx, frame->ecx.argList);
            break;
        
        case CURSOR_DISABLE:
            disableCursor();
            break;
        
        case CURSOR_ENABLE:
            // Control the thickness i suppose
            /* ebx: cursorStart
               ecx: cursorEnd */
            enableCursor((uint8_t)frame->ebx, (uint8_t)frame->ecx.value);
            break;

        case CURSOR_UPDATE:
            /* ebx: x 
               ecx: y */
            updateCursor((uint8_t)frame->ebx, (uint8_t)frame->ecx.value);
            break;
        
        default:
            badSyscall(__func__);
            break;
    }
}

// int32_t generalizes the values that could be returned which is why it's used here
// And because anything to do with syscalls should be using 4 bytes, it's perfect
int32_t sysIn(const struct syscallFrame* frame)
{
    switch (frame->edx)
    {
        case GET_KEY_CHAR:
        {
            char key = getKeyChar();
            return (int32_t)key;
        }

        default:
            badSyscall(__func__);
            break;
    }

    return 0;
}