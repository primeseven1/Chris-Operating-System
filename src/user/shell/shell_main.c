#include <libc/stdio.h>
#include <libc/stdlib.h>
#include "./input/user_input.h"

void shell_main()
{
    cursorEnable(15, 15);
    moveCursor(1, 2);

    printf("Work in progress\n");

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