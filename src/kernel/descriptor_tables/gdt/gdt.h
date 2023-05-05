#pragma once

#include <stdint.h>

typedef enum
{
    GDT_ENTRY_NULL = 0x00,
    GDT_ENTRY_KERNEL_CODE = 0x08,
    GDT_ENTRY_KERNEL_DATA = 0x10,
    GDT_ENTRY_USER_CODE = 0x18,
    GDT_ENTRY_USER_DATA = 0x20,
    GDT_ENTRY_TSS = 0x28,
} segment_t;

// Meant to be used with a bitwise OR operation for each flag, which will add up to the correct access flag
enum gdtAccessFlags
{
    GDT_ACCESS_CODE_READABLE = 0x02,
    GDT_ACCESS_DATA_WRITEABLE = 0x02,
    GDT_ACCESS_CODE_CONFORMING = 0x04,
    GDT_ACCESS_DATA_DIRECTION_NORMAL = 0x00,
    GDT_ACCESS_DATA_DIRECTION_DOWN = 0x04,
    GDT_ACCESS_DATA_SEGMENT = 0x10,
    GDT_ACCESS_CODE_SEGMENT = 0x18,
    GDT_ACCESS_DESCRIPTOR_TSS = 0x09,
    GDT_ACCESS_RING0 = 0x00,
    GDT_ACCESS_RING1 = 0x20,
    GDT_ACCESS_RING2 = 0x40,
    GDT_ACCESS_RING3 = 0x60,
    GDT_ACCESS_PRESENT = 0x80
};

// Also meant to be used with a bitwise OR operation to add up to the correct flags value
enum granularityFlags
{
    GDT_FLAG_64BIT = 0x20,
    GDT_FLAG_32BIT = 0x40,
    GDT_FLAG_16BIT = 0x00,
    GDT_FLAG_GRANULARITY_1B = 0x00,
    GDT_FLAG_GRANULARITY_4K = 0x80
};

void GDTSetEntry(segment_t segment, uint16_t limitLow, uint32_t base, uint8_t accessByte, uint8_t granularity);
void initGDT();