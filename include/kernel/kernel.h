#pragma once

#ifndef RING0
#warning "Only ring 0 needs kernel.h"
#endif

#ifdef RING0

#include <stddef.h>

#define ASM_LINKAGE cdecl

/* This is here just to say that the function could return any type
   You would typically manually store the return value in a register like eax (which is the normal register for return values)
   and then it's up to the calling function to interpret that as the right type */
typedef void anyType_t;

static inline void __attribute__((always_inline)) cli() { asm volatile("cli"); }
static inline void __attribute__((always_inline)) sti() { asm volatile("sti"); }

#endif // RING0