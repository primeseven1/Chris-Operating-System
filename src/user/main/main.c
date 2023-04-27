#include <libc/stdio.h>
#include <libc/string.h>
#include <libc/stdlib.h>
#include <stddef.h>

void umain()
{
    for (;;)
    {
        char character = getChar();

        if  (character == '\b')
        {
            printf("\b \b");
            continue;
        }

        printf("%c", character);
    }
}