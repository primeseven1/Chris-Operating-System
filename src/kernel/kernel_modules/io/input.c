#include <kernel/kernel_modules/io/input.h>
#include <kernel/kernel_modules/io/ports.h>
#include <drivers/keyboard/keyboard.h>

char getKeyChar()
{
    invalid_key_char:
    while (!(inb(KEYBOARD_STATUS_PORT) & KEY_BUFFER_FULL));

    uint8_t key = inb(KEYBOARD_DATA_PORT);
    key = convertScancode(key);

    if (!isPrintable(key))
        goto invalid_key_char;

    return key;
}