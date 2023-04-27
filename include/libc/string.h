#pragma once

#include <stddef.h>

size_t strlen(const char* string);
char* strrev(char* string);
void* memset(void* destination, int value, size_t numOfBytes);
void* memcpy(void* destination, const void* source, size_t numOfBytes);