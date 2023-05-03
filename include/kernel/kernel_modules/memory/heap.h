#pragma once

#ifndef RING0
#warning "Only ring 0 code needs heap.h"
#endif // RING0

#ifdef RING0

#include <stddef.h>

void initHeap();
void* kmalloc(size_t blockSize);
void* kzalloc(size_t blockSize);
void kfree(void* ptr);
void kfreeAll();

#endif // RING0