#pragma once

#include <drivers/graphics/graphics.h>
#include <stdint.h>

void clrscr(vgaColor_t color);
void printf(const char* format, ...);
void changeFgColor(vgaColor_t color);
void changeBgColor(vgaColor_t color);
void moveCursor(uint32_t x, uint32_t y);
void cursorDisable();
void cursorEnable(uint32_t cursorStart, uint32_t cursorEnd);
char getChar();