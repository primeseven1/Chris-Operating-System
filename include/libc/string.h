#pragma once

#include <stddef.h>

// I'm just using this number since it's very unlikely this will be returned by a valid comparison
#define STRCMP_NULL_POINTER_ERROR 654321

size_t strlen(const char* string);
char* strrev(char* string);
int strcmp(const char* string1, const char* string2);
char* strcpy(char* destination, const char* source);
char* strncpy(char* destination, const char* source, size_t numOfChars);
void* memset(void* destination, int value, size_t numOfBytes);
void* memcpy(void* destination, const void* source, size_t numOfBytes);