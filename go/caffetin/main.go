package main

import (
    "fmt"
    "io"
    "time"
    "net/http"
    "sync"
    "caffetin/cache"
)

func fetch(url string) ([]byte, error) {
    resp, err := http.Get(url)
    if (err != nil) {
        return nil, err
    }
    defer resp.Body.Close()
    return io.ReadAll(resp.Body)
}

func fetchAll(cache *cache.Caffetin, urls []string) (chan interface{}) {
    var wg sync.WaitGroup
    result := make(chan interface{}, len(urls))
    for _, url := range urls {
        wg.Add(1)
        go func(url string) {
            defer wg.Done()
            start := time.Now()
            resp, err := cache.Get(url, func(key string) (interface{}, error) {
                return fetch(url)
            })
            if err != nil {
                fmt.Printf("Unable to calculate cache entry %s\n", err)
            } else {
                fmt.Printf("url: %s, time: %s, size: %d\n", url, time.Since(start), len(resp.([]byte)))
                result <- resp
            }
        }(url)
    }

    go func() { 
        wg.Wait() 
        close(result)
    }()

    return result
}

func main() {
    cache := cache.NewCaffetin()
    results := fetchAll(cache, []string{
        "https://example.com",
        "https://google.com",
        "https://example.com",
    })

    for range results {
        fmt.Printf("Content: received\n")
    }
}


