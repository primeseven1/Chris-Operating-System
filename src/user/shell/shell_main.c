#include <libc/stdio.h>

void shell_main()
{
    cursorEnable(15, 15);
    moveCursor(1, 1);

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
            moveCursor(--cursorLocation, 1);
            continue;
        }

        if (cursorLocation > 78)
            continue;

        printf("%c", character);
        moveCursor(++cursorLocation, 1);
        charsOnLine++;
    }
}