#include <assert.h>
#include <stdio.h>
#include <sys/mman.h>

#define MEM_SIZE 1000000

int main() {

    int* mem =  mmap(
        NULL, // hints kernel where to place allocated memory
        MEM_SIZE, // 1MB
        PROT_READ | PROT_WRITE, // Read + Write
        MAP_PRIVATE | MAP_ANONYMOUS, // Not backed by any file
        0, // No file descriptor
        0 // Off set in file
    );

    assert(mem != MAP_FAILED && "Memory not allocated" );

    for (int i = 0; i < 100; i++) {
        mem[i] = i * i;
    }

    for (int i = 0; i < 100; i++) {
        printf("Hello number %i\n", mem[i]);
    }

    munmap(mem, MEM_SIZE);

    return 0;
}
