#pragma once

#ifndef RING0
#warning "Only ring 0 should access video_buffer.h"
#endif // RING0

#ifdef RING0

#include <drivers/graphics/graphics.h>
#include <stdint.h>

#define VIDEO_TEXT_MEMORY (uint16_t*)0xb8000
#define VIDEO_TEXT_MEMORY_MAX VIDEO_TEXT_MEMORY + (V_MODE_WIDTH * V_MODE_HEIGHT)

void updateStruct();
void resetStruct();
uint16_t** getCursorLocationPtr();
uint8_t getCharactersOnLine();
uint8_t getLineNumber();

#endif // RING0