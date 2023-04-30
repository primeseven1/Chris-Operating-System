#include <kernel/kernel_modules/io/input.h>
#include <kernel/kernel_modules/io/ports.h>
#include <drivers/keyboard/keyboard.h>

static inline void shiftPressed(uint8_t key, bool* shifted)
{
    if (key == LEFT_SHIFT_PRESSED || key == RIGHT_SHIFT_PRESSED)
        *shifted = true;
    
    else if (key == LEFT_SHIFT_RELEASED || key == RIGHT_SHIFT_RELEASED)
        *shifted = false;

    else if (key == CAPS_LOCK_PRESSED)
        *shifted = !*shifted;
}

char getKeyChar()
{
    static bool shifted = false;

    invalid_key_char:
    while (!(inb(KEYBOARD_STATUS_PORT) & KEY_BUFFER_FULL));

    uint8_t key = inb(KEYBOARD_DATA_PORT);
    shiftPressed(key, &shifted);

    key = convertScancode(key, shifted);

    if (!isPrintable(key))
        goto invalid_key_char;

    return key;
}