#include <iostream>
#include "map.h"
#include "types.h"

#define COMBINE_TO_KEY( K1, K2 ) K1 < K2 ? (uint64_t)K1 << 32 | (uint64_t)K2 : (uint64_t)K2 << 32 | (uint64_t)K1

struct MyKey {
    MyKey(i32 f, i32 s): first(f), second(s) {}

    ui32 hash() {
        // Murmur hash
        ui64 h = (ui64) first << 32 | (ui64) second;
        h ^= h >> 33;
        h *= 0xff51afd7ed558ccduLL;
        h ^= h >> 33;
        h *= 0xc4ceb9fe1a85ec53uLL;
        h ^= h >> 33;

        return (ui32) h;
    }

    bool operator==(const MyKey& other) const {
        return this->first == other.first && this->second == other.second;
    };

    bool operator!=(const MyKey& other) const {
        return !operator==(other);
    }

    i32 first;
    i32 second;
};

struct MyPayload {
    MyPayload(i32 c, f32 x, f32 y): count(c), x(x), y(y) {}
    i32 count;
    f32 x;
    f32 y;
};

std::ostream& operator<<(std::ostream& os, const MyKey& key) { 
    os << '(' << key.first << " ," << key.second << ')'; 
    return os; 
}

std::ostream& operator<<(std::ostream& os, const MyPayload& payload) { 
    os << "(count = " << payload.count << ", x = " << payload.x << ", y = " << payload.y << ')'; 
    return os; 
}

int main(void) {
    HashMap<MyKey, MyPayload> map;
    map.add(MyKey(12, 74), MyPayload(33, 3.21f, 65.2f));
    map.add(MyKey(72, 21), MyPayload(33, 3.21f, 65.2f));
    map.add(MyKey(89, 95), MyPayload(33, 3.21f, 65.2f));
    map.add(MyKey(96, 58), MyPayload(33, 3.21f, 65.2f));
    map.add(MyKey(96, 58), MyPayload(99, 1234.11f, 8888.78f));

    map.remove(MyKey(89, 95));
    map.debug();

    MyPayload* p = map.get(MyKey(96, 58));
    std::cout << "Retrieved value = " << *p << "\n";

    map.clear();
    map.debug();


    return 1;
}
