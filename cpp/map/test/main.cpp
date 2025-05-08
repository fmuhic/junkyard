#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include "map.h"
#include "murmur3.h"
#include "types.h"


struct MyKey {
    MyKey(i32 f, i32 s): first(f), second(s) {}

    ui32 hash() const {
        return murmurHash3_x86_32(this, sizeof(MyKey), time(NULL));
    }

    inline bool isZero() {
        return first == 0 && second == 0;
    }

    inline void setToZero() {
        first = 0;
        second = 0;
    }

    bool operator==(const MyKey& other) const {
        return this->first == other.first && this->second == other.second;
    };

    i32 first;
    i32 second;
};

ui32 calculateHash(const MyKey* key) {
    // No padding in structure
    return murmurHash3_x86_32(key, sizeof(MyKey), time(NULL));
}

struct MyPayload {
    MyPayload(i32 c, f32 x, f32 y): count(c), x(x), y(y) {}
    i32 count;
    f32 x;
    f32 y;
};

template <>
struct std::hash<MyKey>
{
  std::size_t operator()(const MyKey& k) const
  {
      return k.hash();
  }
};

struct Key {
    Key(i32 x): x(x) {}

    ui32 hash() {
        return murmurHash3_x86_32(this, sizeof(Key), 1);
    }

    bool operator==(const Key& other) const {
        return this->x == other.x;
    };

    inline bool isZero() {
        return x == 0;
    }

    inline void setToZero() {
        x = 0;
    }

    ui32 x;
};

std::ostream& operator<<(std::ostream& os, const MyKey& key) { 
    os << '(' << key.first << " ," << key.second << ')'; 
    return os; 
}

std::ostream& operator<<(std::ostream& os, const MyPayload& payload) { 
    os << "(count = " << payload.count << ", x = " << payload.x << ", y = " << payload.y << ')'; 
    return os; 
}

std::ostream& operator<<(std::ostream& os, const Key& key) { 
    os << '(' << key.x << ')'; 
    return os; 
}

void flush_cache() {
    const size_t bigger_than_cachesize = 100 * 1024 * 1024;
    long *p = new long[bigger_than_cachesize];
    // When you want to "flush" cache. 
    for(int i = 0; i < bigger_than_cachesize; i++)
    {
       p[i] = rand();
    }
    delete [] p;
}

int main(void) {
    HashMap<MyKey, MyPayload> map;
    map.add(MyKey(12, 74), MyPayload(33, 3.21f, 65.2f));
    map.add(MyKey(12, 74), MyPayload(334321, 13.21f, 65.2f));
    map.add(MyKey(72, 21), MyPayload(1, 5.99, 1234.7f));
    map.add(MyKey(89, 95), MyPayload(97, 76.132f, 43.2f));
    map.add(MyKey(96, 58), MyPayload(55, 1.87, 60.3f));
    map.add(MyKey(96, 58), MyPayload(99, 1234.11f, 8888.78f));
    map.add(MyKey(0, 0), MyPayload(11, 123.2f, 543.2f));
    map.add(MyKey(0, 0), MyPayload(22, 77.1f, 1234.321f));

    map.remove(MyKey(89, 95));
    map.debug();

    MyPayload* a = map.get(MyKey(12, 74));
    std::cout << "Get = " << *a << "\n";
    MyPayload* b = map.get(MyKey(72, 21));
    std::cout << "Get = " << *b << "\n";
    MyPayload* c = map.get(MyKey(89, 95)); // missing
    std::cout << "Get = " << c << "\n";
    MyPayload* d = map.get(MyKey(96, 58));
    std::cout << "Get = " << *d << "\n";
    MyPayload* e = map.get(MyKey(0, 0));
    std::cout << "Get = " << *e << "\n";

    map.clear();
    map.debug();

    ui32 x = 1807813940;
    HashMap<Key, ui32> collisions;
    collisions.add(Key(3), 34);
    collisions.add(Key(1807813940), 55);
    collisions.add(Key(0), 876);
    collisions.add(Key(7), 732);
    collisions.add(Key(1807813940), 1234);
    collisions.remove(Key(1807813940));
    collisions.add(Key(1807813940), 0);
    collisions.debug();

    flush_cache();
    std::cout << "__________________________________________\n";
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    HashMap<MyKey, MyPayload> stressMap;
    srand(time(NULL));
    for (i32 i = 0; i < 10000000; ++i) {
        stressMap.add(MyKey(std::rand(), std::rand()), MyPayload(33, 3.21f, 65.2f));
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "INSERT Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    std::cout << "Size = " << stressMap.getSize() << ", capacity = " << stressMap.getCapacity() << "\n";
    std::cout << "__________________________________________\n";

    flush_cache();
    begin = std::chrono::steady_clock::now();
    for (i32 i = 0; i < 10000000; ++i) {
        stressMap.get(MyKey(std::rand(), std::rand()));
    }
    end = std::chrono::steady_clock::now();
    std::cout << "FIND Time difference STD = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    std::cout << "__________________________________________\n";



    flush_cache();
    begin = std::chrono::steady_clock::now();
    std::unordered_map<MyKey, MyPayload> std_map;
    for (i32 i = 0; i < 10000000; ++i) {
        std_map.insert({MyKey(std::rand(), std::rand()), MyPayload(33, 3.21f, 65.2f)});
    }
    end = std::chrono::steady_clock::now();

    std::cout << "INSERT Time difference STD = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    std::cout << "Size STD = " << std_map.size() << "\n";
    std::cout << "__________________________________________\n";

    flush_cache();
    begin = std::chrono::steady_clock::now();
    for (i32 i = 0; i < 10000000; ++i) {
        std_map.find(MyKey(std::rand(), std::rand()));
    }
    end = std::chrono::steady_clock::now();

    std::cout << "FIND Time difference STD = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    std::cout << "Size STD = " << std_map.size() << "\n";
    std::cout << "__________________________________________\n";

    return 1;
}
