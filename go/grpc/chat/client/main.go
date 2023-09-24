package main

import (
    "log"
    "context"
    "google.golang.org/grpc"
    "google.golang.org/grpc/credentials/insecure"
    pb "chat/model"
)

func main() {
    var conn *grpc.ClientConn
    conn, err := grpc.Dial(":9000", grpc.WithTransportCredentials(insecure.NewCredentials()))
    if err != nil {
        log.Fatalf("Unable to connect to gRPC server, %v", err)
    }
    defer conn.Close()

    client := pb.NewChatClient(conn)

    msg := pb.Message{ Body: "Give me money" }

    resp, err := client.SayHello(context.Background(), &msg)
    if err != nil {
        log.Fatalf("Unable say hello, %v", err)
    }

    log.Printf("Response from server: %s", resp.Body)
}
