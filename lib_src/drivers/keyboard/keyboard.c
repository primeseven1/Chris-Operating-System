#include <drivers/keyboard/keyboard.h>

static const char keyboardMap[128] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.', 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

uint8_t convertScancode(uint8_t scancode) 
{
    if (scancode > sizeof(keyboardMap) - 1)
        return 0;

    return keyboardMap[scancode]; 
}

bool isPrintable(uint8_t character)
{
    if (character == 0 || !(character > 31) && !(character < 127))
        return false;

    else if (character == '\t' || character == '\b' || character == '\n')
        return true;

    return true;
}