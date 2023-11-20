#include "alloc.h"

void allocate(Memory *m, ui32 sizeBytes) {
    m->base = (ui8 *) malloc(sizeBytes);
    m->free = m->base;
    m->capacity = sizeBytes;
}

void free(Memory *m) {
    free((void *) m->base);  
}

Block reserve(Memory *m, ui32 elemSizeBytes,  ui32 elemCount) {
    assert(m->free + elemCount * elemSizeBytes <  m->base + m->capacity && "Out of memory");
    Block b = Block {
        m->free,
        elemSizeBytes,
        elemCount
    };
    m->free += elemCount * elemSizeBytes;
    return b;
}
