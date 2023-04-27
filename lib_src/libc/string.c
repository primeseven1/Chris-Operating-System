#include <libc/string.h>

size_t strlen(const char* string)
{
    if (!string)
        return 0;

    size_t i = 0;
    while (string[i] != '\0')
        i++;

    return i;
}

char* strrev(char* string)
{
    if (!string)
        return NULL;

    size_t length = strlen(string);

    for (size_t i = 0, j = length - 1; i < length / 2; i++, j--)
    {
        char buffer = string[i];
        string[i] = string[j];
        string[j] = buffer;
    }

    return string;
}

void* memset(void* destination, int value, size_t numOfBytes)
{
    if (!destination || !numOfBytes) 
        return NULL;

    char* p = destination;

    for (size_t i = 0; i < numOfBytes; i++) 
        p[i] = (char)value;

    return destination;
}

void* memcpy(void* destination, const void* source, size_t numOfBytes)
{
    if (!destination || !source || !numOfBytes) 
        return NULL;

    char* d = (char*)destination;
    const char* s = (const char*)source;

    for (size_t i = 0; i < numOfBytes; i++)
        d[i] = s[i];

    return destination;
}