#pragma once

#include <stddef.h>

void initHeap();
void* kmalloc(size_t blockSize);
void* kzalloc(size_t blockSize);
void kfree(void* ptr);
void kfreeAll();