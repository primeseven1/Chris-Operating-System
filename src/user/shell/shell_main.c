#include <libc/stdio.h>

void shell_main()
{
    printf(">");
    int charsOnLine = 1;

    for (;;)
    {
        char character = getChar();

        if  (character == '\b')
        {
            if (charsOnLine < 2)
                continue;

            printf("\b \b");
            charsOnLine--;
            continue;
        }

        printf("%c", character);
        charsOnLine++;
    }
}