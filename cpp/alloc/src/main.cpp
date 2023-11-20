#include <iostream>
#include <string.h>

#include "alloc.h"
#include "types.h"

#define CAPACITY 32000
#define WORD_MAX_SIZE 50

struct v3 {
    f32 x;
    f32 y;
    f32 z;
};

struct Stuff {
    char word[WORD_MAX_SIZE];
    ui16 wSize = WORD_MAX_SIZE;
    i32 uselesNumber = 55;
};

void printMemInfo(Memory *m) {
    std::cout << "Mem: capacity: " << m->capacity <<
        ", used " << m->free - m->base <<
        ", available " << m->base + m->capacity - m->free << std::endl;
}

int main() {
    Memory m = Memory{};
    allocate(&m, CAPACITY);
    printMemInfo(&m);
    Block vertices = reserve(&m, sizeof(v3), 10);
    printMemInfo(&m);

    for (i32 i = 0; i < vertices.count; i++) {
        v3 *v = get<v3>(vertices, i);
        v->x = i + 100;
        v->y = i + 333;
        v->z = i + 777;
    }

    for (i32 i = 0; i < vertices.count; i++) {
        v3 *v = get<v3>(vertices, i);
        std::cout << "v3(" << v->x << ", " << v->y << ", " << v->z << ")\n";
    }

    Block stuff = reserve(&m, sizeof(Stuff), 10);
    printMemInfo(&m);

    for (i32 i = 0; i < stuff.count; i++) {
        Stuff *s = get<Stuff>(stuff, i);
        strcpy(s->word, "this is not a word!!!");
    }

    for (i32 i = 0; i < stuff.count; i++) {
        Stuff *s = get<Stuff>(stuff, i);
        std::cout << "Stuff(" << s->word << ", " << s->wSize << ", " << s->uselesNumber << ")\n";
    }



    free(&m);
}
