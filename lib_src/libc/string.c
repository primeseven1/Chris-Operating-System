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

int strcmp(const char* string1, const char* string2) 
{
    // If these point to the same memory location, null or not, they have to be equal
    if (!string1 || !string2)
        return STRCMP_NULL_POINTER_ERROR;

    // If the pointers are the same, then they have to be the same
    if (string1 == string2)
        return 0;

    while (*string1 != '\0' && *string2 != '\0') 
    {
        if (*string1 != *string2)
            return *string1 - *string2;

        string1++;
        string2++;
    }

    return *string1 - *string2;
}

char* strcpy(char* destination, const char* source)
{
    if (!destination || !source)
        return NULL;

    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0';
    return destination;
}

char* strncpy(char* destination, const char* source, size_t numOfChars)
{
    if (!destination || !source || numOfChars == 0)
        return NULL;

    while (*source != '\0' && numOfChars != 0)
    {
        *destination = *source;
        source++;
        destination++;
        numOfChars--;
    }

    *destination = '\0';

    return destination;
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