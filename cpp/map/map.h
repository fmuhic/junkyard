#pragma once

#include <assert.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "types.h"

static inline ui32 clz32(ui32 x) {
	return __builtin_clz(x);
}

static inline int roundToPowerOf2(int x) {
    return (x <= 1) ? 1 : 1 << (32 - (int) clz32((ui32) x - 1));
}

template <typename K, typename V>
struct MapItem {
    ui32 hash;
    K key;
    V value;
};

template <typename K, typename V>
class HashMap {
    public:
    HashMap(i32 initCapacity = 16);
    ~HashMap();

    V* get(K key);
    bool add(K key, V value);
    bool remove(K key);
    void clear();

    void debug();

    private:
    // We need move here as well
    void safeAddItem(K key, V value, ui32 hash);
    ui32 findSlot(K key, ui32 hash);
    void growTable();

    MapItem<K, V>* elements;
    ui32 capacity;
    ui32 size;
};

template <typename K, typename V>
HashMap<K,V>::HashMap(i32 initCapacity) {
	// Capacity must be a power of 2
	if (initCapacity > 16) {
		capacity = roundToPowerOf2(initCapacity);
	}
	else {
		capacity = 16;
	}

	size = 0;
	elements = (MapItem<K,V>*) malloc(capacity * sizeof(MapItem<K,V>));
	memset(elements, 0, capacity * sizeof(MapItem<K,V>));
}

template <typename K, typename V>
HashMap<K,V>::~HashMap() {
    free(elements);
}
template <typename K, typename V>
V* HashMap<K,V>::get(K key) {
	ui32 hash = key.hash();
	assert(hash != 0);
	int index = findSlot(key, hash );
    if (elements[index].key == key) {
        return &elements[index].value;
    }
    else {
        return nullptr;
    }
}

template <typename K, typename V>
bool HashMap<K,V>::add(K key, V value) {
	ui32 hash = key.hash();
	assert(hash != 0 && "Hash of zero is a sentinel");

	int index = findSlot(key, hash);
	if (elements[index].hash != 0 )	{
		// Already in set, just replace it
		assert(elements[index].hash == hash && elements[index].key == key);
        elements[index].value = value;
		return true;
	}

	if (2 * size >= capacity) {
		growTable();
	}

	safeAddItem(key, value, hash);
	return false;
}

template <typename K, typename V>
ui32 HashMap<K,V>::findSlot(K key, ui32 hash) {
	int index = hash & (capacity - 1);
	while (elements[index].hash != 0 && elements[index].key != key)	{
		index = (index + 1) & (capacity - 1);
	}

	return index;
}

template <typename K, typename V>
void HashMap<K,V>::growTable() {
    ui32 oldSize = size;
	ui32 oldCapacity = capacity;
	MapItem<K,V>* oldElements = elements;

	size = 0;
	// Capacity must be a power of 2
	capacity = 2 * oldCapacity;
	elements = (MapItem<K,V>*) malloc(capacity * sizeof(MapItem<K,V>));
	memset(elements, 0, capacity * sizeof(MapItem<K,V>));

	// Transfer items into new array
	for (ui32 i = 0; i < oldCapacity; ++i) {
		MapItem<K, V>* item = oldElements + i;
		if (item->hash == 0) {
			// this item was empty
			continue;
		}

		safeAddItem(item->key, item->value, item->hash);
	}

	assert(size == oldSize);
	free(oldElements);
}

template <typename K, typename V>
void HashMap<K,V>::safeAddItem(K key, V value, ui32 hash) {
    ui32 index = findSlot(key, hash);
	assert(elements[index].hash == 0);

	elements[index].key = key;
	elements[index].value = value;
	elements[index].hash = hash;
	++size;
}
template <typename K, typename V>
void HashMap<K,V>::clear() {
    size = 0;
	memset(elements, 0, capacity * sizeof(MapItem<K,V>));
}

template <typename K, typename V>
bool HashMap<K,V>::remove(K key) {
    ui32 hash = key.hash();
	ui32 i = findSlot(key, hash);
	if (elements[i].hash == 0) {
		// Not in set
		return false;
	}

	// Mark item i as unoccupied
	elements[i].hash = 0;

	assert(size > 0);
	--size;

	// Attempt to fill item i
	ui32 j = i;
	while (true) {
		j = ( j + 1 ) & ( capacity - 1 );
		if (elements[j].hash == 0)	{
			break;
		}

		// k is the first item for the hash of j
		int k = elements[j].hash & ( capacity - 1 );

		// determine if k lies cyclically in (i,j]
		// i <= j: | i..k..j |
		// i > j: |.k..j  i....| or |....j     i..k.|
		if (i <= j)	{
			if ( i < k && k <= j ) {
				continue;
			}
		}
		else {
			if (i < k || k <= j) {
				continue;
			}
		}

		// Move j into i
		elements[i] = elements[j];

		// Mark item j as unoccupied
		elements[j].hash = 0;

		i = j;
	}

	return true;
}

template <typename K, typename V>
void HashMap<K,V>::debug() {
    std::cout << "Map, size = " << size << ", capacity = " << capacity << "\n";
    for (i32 i = 0; i < capacity; ++i) {
        MapItem<K, V> item = elements[i];
        if (item.hash == 0) continue;

        std::cout << "Item " << i << ": K = " << item.key << ",  V = " << item.value << "\n";
    }
}
