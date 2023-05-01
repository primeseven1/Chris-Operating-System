#pragma once

#ifndef RING0
#warning "Only ring 0 needs to use cursor.h, nothing is included in this header file"
#endif // RING0

#ifdef RING0

#include <stdint.h>
#include <stdbool.h>

void enableCursor(uint8_t cursorStart, uint8_t cursorEnd);
void disableCursor();
void updateCursor(uint8_t x, uint8_t y);
bool getCursorStatusEnabled();
uint8_t getPositionX();
uint8_t getPositionY();

#endif // RING0