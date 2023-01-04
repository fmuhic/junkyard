use log::{info, error};
use std::net::{TcpListener, TcpStream};
use std::io::Write;

fn serve_connection(mut stream: TcpStream) -> Result<(), String> {
    let body = "<html><head></head><body>hello</body></html>".to_string();
    let response = format!("{}{}", "HTTP/1.1 200 OK\r\n\r\n", body);
    stream.write(response.as_bytes()).unwrap();
    Ok(())
}

fn main() {
    simple_logger::init().unwrap();
    let ip = "127.0.0.1:8888";

    info!("Starting server ...");
    let listener = TcpListener::bind(ip).expect("Unable to create TCP listener!");
    info!("Server started listening on: {}{}", "http://", ip);

    for connection in listener.incoming() {
        match connection {
            Ok(stream) => match serve_connection(stream) {
                Ok(_) => {},
                Err(e) => error!("Error while serving connection: {}", e)
            },
            Err(e) => error!("Connection failed: {}", e)
        }
    }
}
