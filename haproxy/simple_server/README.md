# HAProxy

### Setup

Create image:
```sh
$ docker build . -t simple-server
```

Run multiple containers:
``` bash
$ docker run -e SERVER_ID=1 -d -p 9090:8080 simple-server
$ docker run -e SERVER_ID=2 -d -p 9091:8080 simple-server
$ docker run -e SERVER_ID=3 -d -p 9092:8080 simple-server
$ docker run -e SERVER_ID=4 -d -p 9093:8080 simple-server
```
