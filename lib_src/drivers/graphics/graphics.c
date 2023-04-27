#include <stddef.h>
#include "./video_buffer.h"

static uint16_t** cursorLocationPtr = NULL;

static void handleEscapeChar(unsigned char character)
{
    switch (character)
    {
        case '\b':
        {
            (*cursorLocationPtr)--;
            updateStruct();
            break;
        }

        case '\r':
        {
            uint8_t charsOnLine = getCharactersOnLine();        
            *cursorLocationPtr -= charsOnLine;
            
            updateStruct();
            break;
        }

        case '\n':
        {
            if (getLineNumber() == 25)
                return;

            uint8_t charsOnLine = getCharactersOnLine();
            *cursorLocationPtr += V_MODE_WIDTH - charsOnLine;

            updateStruct();
            break;
        }

        case '\t':
        {
            uint8_t charsOnLine = getCharactersOnLine();
            
            // Brings the cursor to the end of the line if there isn't enough space for the tab
            if (charsOnLine > V_MODE_WIDTH - 4)
                *cursorLocationPtr += V_MODE_WIDTH - charsOnLine;
            
            else
                *cursorLocationPtr += 4;

            updateStruct();
            break;
        }
    }
}

// Getting around the function call not allowed in a constant value issue
void initGraphicsDriver() { cursorLocationPtr = getCursorLocationPtr(); }

void printChar(unsigned char character, vgaColor_t fgColor, vgaColor_t bgColor)
{
    if (!cursorLocationPtr)
        return;
        
    if (character == '\b' || character == '\r' ||
        character == '\n' || character == '\t')
    {
        if (*cursorLocationPtr == VIDEO_TEXT_MEMORY && 
            character != '\n' && character != '\t')
            return;

        handleEscapeChar(character);
        return;
    }

    if (*cursorLocationPtr == VIDEO_TEXT_MEMORY_MAX)
        return;

    uint8_t attributeByte = (bgColor << 4) | (fgColor & 0x0F);

    **cursorLocationPtr = (character | (attributeByte << 8));
    (*cursorLocationPtr)++;
    updateStruct();
}

void printString(const char* string, vgaColor_t fgColor, vgaColor_t bgColor)
{
    if (!string || !cursorLocationPtr)
        return;

    while (*string != '\0')
    {
        printChar(*string, fgColor, bgColor);
        string++;
    }
}

void clearScreen(vgaColor_t color)
{
    if (!cursorLocationPtr)
        return;

    // Set the location at the beginning so the screen can be cleared
    *cursorLocationPtr = VIDEO_TEXT_MEMORY;

    uint8_t attributeByte = (color << 4) | (color & 0x0F);

    // Clears the screen by setting the entire video buffer to spaces
    for (int i = 0; i < V_MODE_WIDTH * V_MODE_HEIGHT; i++, (*cursorLocationPtr)++)
        **cursorLocationPtr = (' ' | (attributeByte << 8));

    resetStruct();
}