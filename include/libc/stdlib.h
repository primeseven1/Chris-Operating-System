#pragma once

#include <stddef.h>

char* itoa(int value, char* destination, unsigned int base);
char* ftoa(float value, char* destination, unsigned int precision);
void* malloc(size_t blockSize);
void* calloc(size_t elements, size_t sizeOfElement);
void free(void* ptr);