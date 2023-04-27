#pragma once

#include <stdarg.h>

void vkprintf(const char* format, va_list args);
void kprintf(const char* format, ...);