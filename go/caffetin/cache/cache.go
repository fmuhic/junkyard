package cache

import "fmt"

type Func func(key string) (interface{}, error)

type Caffetin struct {
    data map[string]interface{}
}

func NewCaffetin() *Caffetin {
    return &Caffetin{
        data: make(map[string]interface{}),
    }
}

func (c *Caffetin) Get(key string, getEntry Func) (interface{}, error) {
    entry, ok := c.data[key]
    if !ok {
        value, err := getEntry(key)
        if err != nil {
            fmt.Printf("Error while evalutaing getEntry function %s\n", err)
            return nil, err
        }
        c.data[key] = value
        return value, nil
    }
    return entry, nil
}
