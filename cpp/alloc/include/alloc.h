#pragma once

#include <malloc.h>
#include <assert.h>

#include "types.h"

struct Block {
    ui8 *mem;
    ui32 sizeBytes;
    ui32 count;
};

struct Memory {
    ui8 *base;
    ui8 *free;
    ui32 capacity;
};

void allocate(Memory *m, ui32 sizeBytes);
void free(Memory *m);
Block reserve(Memory *m, ui32 elemSizeBytes,  ui32 elemCount);

template <typename T>
T* get(Block b, ui32 index) {
    assert(index < b.count && "Out of bounds");
    return (T*) b.mem + b.sizeBytes * index; 
}
