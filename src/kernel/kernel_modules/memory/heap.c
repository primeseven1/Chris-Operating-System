#include <kernel/kernel_modules/io/panic.h>
#include <libc/string.h>
#include <stdbool.h>
#include "./heap.h"

// currentReserved is used to prevent allocating memory outside of the heap memory space
static struct
{
    void* heapStart;
    void* heapEnd;
    size_t heapSize;
    size_t currentReserved;
} heap;

/* blockSize will only have a value that is not 0 if the pointer that is selected isn't free
   however, it is mostly used for freeing memory so it knows which blocks to free
   I may impliment it in my kmalloc function to determine what address to choose later */
struct free
{
    void* ptr;
    size_t blockSize;
    bool free;
};

// This is where the information about pointers in the heap are going to be located, storing this on the stack would take up the entire stack
static struct free* freeBlocks = (struct free*)0x1000000;

static bool init = false;
void initHeap()
{
    // Making sure the heap isn't initialized twice
    if (init)
        return;

    // 64 KB of heap space
    heap.heapStart = (void*)0x900000;
    heap.heapSize = 65536;
    heap.heapEnd = heap.heapStart + heap.heapSize;
    heap.currentReserved = 0;

    // Initializing the free list
    for (size_t i = 0; i < heap.heapSize; i++)
    {
        struct free freeBlock = { .ptr = heap.heapStart + i, .blockSize = 0, .free = true };
        freeBlocks[i] = freeBlock;
    }

    init = true;
}

void* kmalloc(size_t blockSize)
{
    if (!init)
        return NULL;

    // Making sure the requested block size isn't too big, or if the block size is zero
    if (!blockSize || blockSize > heap.heapSize
        || heap.currentReserved + blockSize > heap.heapSize)
        return NULL;
    
    for (size_t i = 0; i < heap.heapSize; i++)
    {
        bool good = false;

        if (freeBlocks[i].free)
        {
            // Checking if the requested block size is big enough
            for (size_t j = 0; j < blockSize; j++)
            {
                if (freeBlocks[i + j].free)
                    good = true;
                
                else
                {
                    good = false;
                    break;
                }
            }
        }

        // Setting all the blocks of memory to not free and returning the pointer
        if (good)
        {
            freeBlocks[i].free = false;

            for (size_t j = 0; j < blockSize; j++)
                freeBlocks[i + j].free = false;

            // Setting the block size for freeing, and adding how much is reserved
            freeBlocks[i].blockSize = blockSize;
            heap.currentReserved += blockSize;
            return freeBlocks[i].ptr;
        }
    }

    // If it reaches here, there is no block size big enough
    return NULL;
}

void* kzalloc(size_t blockSize)
{
    void* ptr = kmalloc(blockSize);
    if (!ptr)
        return NULL;

    memset(ptr, 0, blockSize);
    return ptr;
}

void kfree(void* ptr)
{
    if (!init)
        return;

    // This is preventing marking memory as free at a different location than the heap
    // Since it could cause problems in the future when they try to free memory that isn't in the memory pool, the kernel will panic
    if ((int)ptr < (int)heap.heapStart || (int)ptr > (int)heap.heapEnd)
    {
    panic:
        struct panicInfo panicInfo = { 
            .errorCode = KERNEL_HEAP_ERROR, 
            .memoryAddress = ptr, 
            .info = "There was an attempt to free memory outside of the heap",
            .caller = __func__ 
        };

        kpanic(&panicInfo);
    }

    size_t i = 0;
    for (; i < heap.heapSize; i++)
    {
        if (freeBlocks[i].ptr == ptr)
            break;
    }

    // If the pointer that was set to be freed had a block size of zero, that can become a problem
    if (freeBlocks[i].blockSize == 0)
    {
        struct panicInfo panicInfo = {
            .errorCode = KERNEL_HEAP_ERROR,
            .memoryAddress = ptr,
            .info = "There was an attempt to free memory, but the block size was 0",
            .caller = __func__
        };

        kpanic(&panicInfo);
    }

    for (int j = 0; j < freeBlocks[i].blockSize; j++)
    {
        /* I'm using a goto statement here since the error information would be the exact same anyway
           when the kernel panics, it has an infinite loop anyway to stop the kernel */
        if ((int)(freeBlocks[i + j].ptr) > (int)heap.heapEnd)
            goto panic;

        freeBlocks[i + j].free = true;
    }

    // Subtrating how much memory is reserved, and resetting the block size to zero
    heap.currentReserved -= freeBlocks[i].blockSize;
    freeBlocks[i].blockSize = 0;
}