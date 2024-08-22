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

func fetchAll(cache *cache.Caffetin[[]byte], urls []string) (chan []byte) {
    var wg sync.WaitGroup
    result := make(chan []byte, len(urls))
    for _, url := range urls {
        wg.Add(1)
        go func(url string) {
            defer wg.Done()
            start := time.Now()
            resp, err := cache.Get(url, fetch)
            if err != nil {
                fmt.Printf("Unable to calculate cache entry %s\n", err)
            } else {
                fmt.Printf("url: %s, time: %s, size: %d\n", url, time.Since(start), len(resp))
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
    cache := cache.NewCaffetin[[]byte]()
    results := fetchAll(cache, []string{
        "https://example.com",
        "https://google.com",
        "https://example.com",
    })

    for range results {
        fmt.Printf("Content: received\n")
    }
}


