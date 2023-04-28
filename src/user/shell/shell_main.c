#include <libc/stdio.h>

void shell_main()
{
    cursorEnable(15, 15);
    moveCursor(1, 2);

    printf("Work in progress\n\n");

    // The X of the cursor location
    // TODO: Improve this later
    int cursorLocation = 1;

    printf(">");
    int charsOnLine = 1;

    for (;;)
    {
        char character = getChar();

        // Handle tabs later
        if (character == '\n' || character == '\t')
            continue;

        if  (character == '\b')
        {
            if (charsOnLine < 2)
                continue;

            printf("\b \b");
            charsOnLine--;
            moveCursor(--cursorLocation, 2);
            continue;
        }

        if (cursorLocation > 78)
            continue;

        printf("%c", character);
        moveCursor(++cursorLocation, 2);
        charsOnLine++;
    }
}