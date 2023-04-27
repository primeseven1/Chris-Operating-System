#include <libc/stdlib.h>
#include <libc/string.h>
#include <stdbool.h>
#include <stddef.h>

char* itoa(int value, char* destination, unsigned int base) 
{
    if (!destination || !base || base > 36)
        return NULL;

    /* Define a character array to store the converted string 
       + use a memset to prevent values from previous function calls from being included */
    char buffer[33];
    memset(buffer, 0, sizeof(buffer));

    int i = 0;
    bool negative = false;

    // Handle negative integers
    if (value < 0) 
    {
        negative = true;
        value = -value;
    }

    // Convert the integer to a string
    do 
    {
        buffer[i++] = "0123456789abcdefghijklmnopqrstuvwxyz"[value % base];
        value /= base;
    } 
    while (value);

    // Add the negative sign if necessary
    if (negative)
        buffer[i++] = '-';

    // Add the null terminator to the string
    buffer[i] = '\0';

    // Reverse the string and copy it to the output buffer
    size_t length = strlen(buffer);

    for (size_t j = 0; j < length; j++) 
        destination[j] = buffer[length - j - 1];
    
    return destination;
}

char* ftoa(float value, char* destination, unsigned int precision)
{
    if (!destination)
        return NULL;

    bool negative = false;

    if (value < 0) 
    {
        negative = true;
        value = -value;
    }

    /* Deine character array 
       + Preventing values from previous function calls from being included */
    char buffer[64];
    memset(buffer, 0, sizeof(buffer));

    int i = 0;

    // Extract the integer part of the value
    int integerPart = (int)value;

    // Add digits to the buffer for the integer part
    do 
    {
        buffer[i++] = '0' + (integerPart % 10);
        integerPart /= 10;
    } 
    while (integerPart);

    // Add the negative part first
    if (negative) 
        buffer[i++] = '-';
    
    // Reverse the integer part of the buffer
    int integerLength = i;
    for (int j = 0; j < integerLength / 2; j++) 
    {
        char temp = buffer[j];
        buffer[j] = buffer[integerLength - j - 1];
        buffer[integerLength - j - 1] = temp;
    }

    // Resetting this value back to remove the bug where there would just be a random character after the decimal
    integerPart = (int)value;

    // Add decimal point and digits for the fractional par
    if (precision) 
    {
        buffer[i++] = '.';
        float fractionalPart = value - (float)integerPart;
        while (precision) 
        {
            fractionalPart *= 10.f;
            int digit = (int)fractionalPart;
            buffer[i++] = '0' + (char)digit;
            fractionalPart -= digit;
            precision--;
        }
    }

    buffer[i] = '\0';

    size_t length = strlen(buffer);
    for (size_t j = 0; j < length; j++)
        destination[j] = buffer[j];

    return destination;
}

void* malloc(size_t blockSize)
{
    if (!blockSize)
        return NULL;

    void* ptr = NULL;

    /* 0x03: The request memory system call
       ebx: The block size */
    asm volatile("mov $0x3, %eax");
    asm volatile("mov %0, %%ebx" : : "m"(blockSize));
    asm volatile("int $0x80");

    // Storing the return value from the system call in the pointer variable
    asm volatile("mov %%eax, %0" : "=r"(ptr));

    return ptr;
}

void* calloc(size_t elements, size_t sizeOfElement)
{
    void* ptr = malloc(elements * sizeOfElement);

    if (!ptr)
        return ptr;

    memset(ptr, 0, elements * sizeOfElement);
    return ptr;
}

void free(void* ptr)
{
    if (!ptr)
        return;

    /* 0x04: The system call for freeing memory 
       ebx: The pointer to be freed */
    asm volatile("mov $0x4, %eax");
    asm volatile("mov %0, %%ebx" : : "m"(ptr));
    asm volatile("int $0x80");
}