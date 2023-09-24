package main

import (
    "log"
    "net"
    "context"
    "google.golang.org/grpc"
    pb "chat/model"
)

type Server struct {
    pb.UnimplementedChatServer
}

func (c *Server) SayHello(ctx context.Context, msg *pb.Message) (*pb.Message, error) {
    log.Printf("Received message Client: %s", msg.Body)
    return &pb.Message{ Body: "Hello from server" }, nil
}

func main() {
    listener, err := net.Listen("tcp", ":9000")
    if err != nil {
        log.Fatalf("Unable to start server at port 9000, %v", err)
    }

    grpcServer := grpc.NewServer()

    pb.RegisterChatServer(grpcServer, &Server{})

    if err := grpcServer.Serve(listener); err != nil {
        log.Fatalf("Failed to server gRPC, %v", err)
    }
}
