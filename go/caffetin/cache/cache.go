package cache

import (
    "fmt"
    "sync"
)

type Func[T any] func(key string) (T, error)

func Zero[T any]() T {
    var zero T
    return zero
}

type Caffetin[T any] struct {
    lock sync.Mutex
    data map[string]T
}

func NewCaffetin[T any]() *Caffetin[T] {
    return &Caffetin[T]{
        lock: sync.Mutex{},
        data: make(map[string]T),
    }
}

func (c *Caffetin[T]) Get(key string, getEntry Func[T]) (T, error) {
    entry, ok := c.data[key]
    if !ok {
        newEntry, err := getEntry(key)
        if err != nil {
            fmt.Printf("Error while evalutaing getEntry function %s\n", err)
            return Zero[T](), err
        }

        c.lock.Lock()
        c.data[key] = newEntry
        c.lock.Unlock()

        return newEntry, nil
    }
    return entry, nil
}
