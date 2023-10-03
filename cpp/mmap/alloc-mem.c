#include <assert.h>
#include <stdio.h>
#include <sys/mman.h>

#define N 10 

int main() {

    int* mem = mmap(
        NULL, // hints kernel where to place allocated memory
        N * sizeof(int),
        PROT_READ | PROT_WRITE, // Read + Write
        MAP_PRIVATE | MAP_ANONYMOUS, // Not backed by any file
        0, // No file descriptor
        0 // Off set in file
    );

    assert(mem != MAP_FAILED && "Memory not allocated" );

    for (int i = 0; i < N; i++) {
        mem[i] = i * i;
    }

    for (int i = 0; i < N; i++) {
        printf("Hello number %i\n", mem[i]);
    }

    int err = munmap(mem, N * sizeof(int));
    assert(err >= 0 && "Unable to deallocate memory" );

    return 0;
}
