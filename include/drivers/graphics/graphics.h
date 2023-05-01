#pragma once

// These can be useful to have at ring 3, so these are kept
#define V_MODE_WIDTH 80
#define V_MODE_HEIGHT 25

typedef enum
{
    VGA_BLACK,
    VGA_BLUE,
    VGA_GREEN,
    VGA_CYAN,
    VGA_RED,
    VGA_MAGENTA,
    VGA_BROWN,
    VGA_LIGHT_GREY,
    VGA_DARK_GREY,
    VGA_LIGHT_BLUE,
    VGA_LIGHT_GREEN,
    VGA_LIGHT_CYAN,
    VGA_LIGHT_RED,
    VGA_LIGHT_MAGENTA,
    VGA_LIGHT_BROWN,
    VGA_WHITE
} vgaColor_t;

// These are only meant to be called within kernel level, so no need to include these
// Attempting to use these at user level will result in a linker error anyway
#ifdef RING0

#include <stdint.h>

void initGraphicsDriver();
void printChar(unsigned char character, vgaColor_t fgColor, vgaColor_t bgColor);
void printString(const char* string, vgaColor_t fgColor, vgaColor_t bgColor);
void clearScreen(vgaColor_t color);
uint8_t getCharactersOnLine();
uint8_t getLineNumber();

#endif // RING0