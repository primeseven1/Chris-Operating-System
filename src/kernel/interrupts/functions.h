#pragma once

#include <kernel/kernel.h>
#include "./callFrames.h"

#define HW_INTERRUPT interrupt
#define TRAP interrupt

void kernelModeTrap(const char* caller, void* memoryAddress);

void __attribute__((HW_INTERRUPT)) mce(const struct exceptionCallFrame* frame);

void __attribute__((TRAP)) gpf(const struct exceptionCallFrame* frame);
void __attribute__((TRAP)) divideByZero(const struct exceptionCallFrame* frame);
void __attribute__((TRAP, ASM_LINKAGE)) syscall_handle(const void* unusedFrame);