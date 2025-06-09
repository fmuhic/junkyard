### EC2

- Start docker in user data
```sh
#!/bin/bash
# Update the package index
dnf update -y

# Install Docker
dnf install docker -y

# Start the Docker service
systemctl start docker

# Enable Docker to start on boot
systemctl enable docker

# Add ec2-user to docker group (so you can run docker without sudo)
usermod -aG docker ec2-user
```

- Start nginx inside docker
```sh
# Create index.html in ~/web folder and run nginx
docker run -d -p 80:80 -v ~/web:/usr/share/nginx/html nginx
```
