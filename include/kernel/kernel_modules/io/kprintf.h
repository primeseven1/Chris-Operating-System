#pragma once

#ifndef RING0
#warning "Only ring 0 needs kprintf.h"
#endif // RING0

#ifdef RING0

#include <stdarg.h>

void vkprintf(const char* format, va_list args);
void kprintf(const char* format, ...);

#endif // RING0