#include <stdio.h>

#define CAPACITY 640000

char heap[CAPACITY] = {0};

void * heap_alloc(size_t size) {
    return NULL;
}

void heap_free(void *ptr) {
}

int main() {
    char x[] = "hello world";
    int i = 0;
    printf("%i\n", i);
    printf("%s\n", x);
    return 0;
}
