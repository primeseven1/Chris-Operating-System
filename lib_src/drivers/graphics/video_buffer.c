#include "./video_buffer.h"

// Struct to represent the video text buffer
// Line number and characters on line is based on the cursor location
static struct
{
    uint16_t* cursorLocation;
    uint8_t lineNumber;
    uint8_t charactersOnLine;
} videoTextBuffer = {
    .cursorLocation = VIDEO_TEXT_MEMORY,
    .lineNumber = 1,
    .charactersOnLine = 0 
};

void updateStruct()
{
    // The cursor location is stored as a uint16_t*, so the cursor has to be divided by the size of a uint16_t (2)
    uint32_t cursorOffset = (uint32_t)videoTextBuffer.cursorLocation - (uint32_t)VIDEO_TEXT_MEMORY;
    videoTextBuffer.lineNumber = cursorOffset / V_MODE_WIDTH / sizeof(uint16_t) + 1;
    videoTextBuffer.charactersOnLine = cursorOffset % (80 * sizeof(uint16_t)) / sizeof(uint16_t);
}

void resetStruct()
{
    videoTextBuffer.cursorLocation = VIDEO_TEXT_MEMORY;
    videoTextBuffer.lineNumber = 1;
    videoTextBuffer.charactersOnLine = 0;
}

uint16_t** getCursorLocationPtr() { return &videoTextBuffer.cursorLocation; }

uint8_t getCharactersOnLine() { return videoTextBuffer.charactersOnLine; }

uint8_t getLineNumber() { return videoTextBuffer.lineNumber; }