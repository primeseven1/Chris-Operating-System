#include <kernel/kernel_modules/io/ports.h>
#include <drivers/graphics/graphics.h>

#define VGA_CTRL_PORT 0x3D4
#define VGA_DATA_PORT 0x3D5

static struct
{
	uint8_t cursorStart;
	uint8_t cursorEnd;
	uint8_t positonX;
	uint8_t positionY;
} cursorAttributes = {
	.cursorStart = 0,
	.cursorEnd = 0,
	.positonX = 0,
	.positionY = 0
};

void enableCursor(uint8_t cursorStart, uint8_t cursorEnd)
{
	// The max number is 15 for both
	if (cursorStart > 15)
		cursorStart = 15;

	if (cursorEnd > 15)
		cursorEnd = 15;

	outb(VGA_CTRL_PORT, 0x0A);
	outb(VGA_DATA_PORT, (inb(VGA_DATA_PORT) & 0xC0) | cursorStart);
 
	outb(VGA_CTRL_PORT, 0x0B);
	outb(VGA_DATA_PORT, (inb(VGA_DATA_PORT) & 0xE0) | cursorEnd);

	cursorAttributes.cursorStart = cursorStart;
	cursorAttributes.cursorEnd = cursorEnd;
}

void disableCursor()
{
    outb(VGA_CTRL_PORT, 0x0A);
	outb(VGA_DATA_PORT, 0x20);
}

void updateCursor(uint8_t x, uint8_t y)
{
	// The cursor position x and y start at 0 which is why it's subtracted by 1
	if (x > V_MODE_WIDTH - 1)
		x = V_MODE_WIDTH - 1;
	
	if (y > V_MODE_HEIGHT - 1)
		y = V_MODE_HEIGHT - 1;

	uint16_t pos = y * V_MODE_WIDTH + x;
 
	outb(VGA_CTRL_PORT, 0x0F);
	outb(VGA_DATA_PORT, (pos & 0xFF));
	outb(VGA_CTRL_PORT, 0x0E);
	outb(VGA_DATA_PORT, ((pos >> 8) & 0xFF));

	cursorAttributes.positonX = x;
	cursorAttributes.positionY = y;
}