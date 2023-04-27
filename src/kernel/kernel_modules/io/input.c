#include <kernel/kernel_modules/io/input.h>
#include <kernel/kernel_modules/io/ports.h>
#include <drivers/keyboard/keyboard.h>

char getKeyChar()
{
    try_again:
    while (!(inb(KEYBOARD_STATUS_PORT) & KEY_BUFFER_FULL));

    uint8_t key = inb(KEYBOARD_DATA_PORT);
    key = convertScancode(key);

    if (!isPrintable(key))
        goto try_again;

    return key;
}