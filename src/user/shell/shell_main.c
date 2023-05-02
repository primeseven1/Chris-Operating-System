#include <libc/stdio.h>
#include <libc/stdlib.h>
#include "./input/user_input.h"

void shell_main()
{
    // Make the cursor thin and set the cursor to where it will be after going into the shell
    cursorEnable(15, 15);
    moveCursor(1, 2);

    changeFgColor(VGA_RED);
    changeBgColor(VGA_DARK_GREY);
    
    printf("Work in progress\n");

    changeFgColor(VGA_WHITE);
    changeBgColor(VGA_BLACK);

    for (;;)
    {
        // Heap allocated
        const char* input = userInput();

        if (!input)
        {
            printf("Error with allocating memory");
            for (;;);
        }

        printf("\nYou entered:\n%s", input);
        free(input);
    }
}
