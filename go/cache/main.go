package main

import (
    "fmt"
    "io"
    "time"
    "net/http"
    "sync"
)

type HttpResult struct {
    content []byte
    err error
}

func NewHttpResult(content []byte, err error) (HttpResult) {
    return HttpResult{ content, err }
}

func fetch(url string) HttpResult {
    resp, err := http.Get(url)
    if (err != nil) {
        return NewHttpResult(nil, err)
    }
    defer resp.Body.Close()
    return NewHttpResult(io.ReadAll(resp.Body))
}

func fetchAll(urls []string) (chan HttpResult) {
    var wg sync.WaitGroup
    result := make(chan HttpResult, len(urls))
    for _, url := range urls {
        wg.Add(1)
        go func(url string) {
            defer wg.Done()
            start := time.Now()
            resp :=  fetch(url)
            fmt.Printf("url: %s, time: %s, size: %d\n", url, time.Since(start), len(resp.content))
            result <- resp
        }(url)
    }

    go func() { 
        wg.Wait() 
        close(result)
    }()

    return result
}

func main() {
    results := fetchAll([]string{
        "https://example.com",
        "https://google.com",
        "https://example.com",
    })

    for r := range results {
        if (r.err != nil) {
            fmt.Printf("Error while fetching content %s\n", r.err)
        } else {
            fmt.Printf("Content: received\n")
        }
    }
}


