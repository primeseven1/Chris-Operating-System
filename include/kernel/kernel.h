#pragma once

#include <stddef.h>

#define ASM_LINKAGE cdecl

/* This is here just to say that the function could return any type
   You would typically manually store the return value in a register like eax
   and then it's up to the calling function to interpret that as the right type */
typedef void anyType_t;

static inline void __attribute__((always_inline)) cli() { asm volatile("cli"); }
static inline void __attribute__((always_inline)) sti() { asm volatile("sti"); }