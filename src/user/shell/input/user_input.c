#include <libc/stdio.h>
#include <libc/stdlib.h>
#include <libc/string.h>

const char* userInput()
{
    // The X of the cursor location
    // TODO: Improve this later
    
    // Max line number (79) + null terminator
    char* input = (char*)malloc(V_MODE_WIDTH);

    if (!input)
        return NULL;

    memset(input, 0, V_MODE_WIDTH);
    int cursorLocationX = 1;
    static int cursorLocationY = 2;

    if (cursorLocationY > 24)
    {
        // Clear the screen if the text is going to go off the screen
        clrscr(VGA_BLACK);
        cursorLocationY = 1;
        moveCursor(cursorLocationX, cursorLocationY);
    }

    printf("\n>");
    int charsOnLine = 1;

    for (;;)
    {
        char character = getChar();

        switch (character)
        {
            case '\t':
                continue;
                break;
            
            case '\n':
                input[charsOnLine - 1] = '\0';
                cursorLocationY += 3;
                moveCursor(1, cursorLocationY);
                return input;
                break;
            
            case '\b':
                if (charsOnLine < 2)
                    continue;

                printf("\b \b");
                input[charsOnLine - 1] = ' ';
                charsOnLine--;
                moveCursor(--cursorLocationX, cursorLocationY);
                continue;
                break;
            
            default:
                if (cursorLocationX > 78)
                    continue;

                printf("%c", character);
                moveCursor(++cursorLocationX, cursorLocationY);
                input[charsOnLine - 1] = character;
                charsOnLine++;
                break;
        }
    }
}
