### EC2

- Start docker in user data
```sh
#!/bin/bash
# Update the package index
dnf update -y

# Install Docker
dnf install docker certbot git -y

# Start the Docker service
systemctl start docker

# Enable Docker to start on boot
systemctl enable docker

# Add ec2-user to docker group (so you can run docker without sudo)
usermod -aG docker ec2-user

# Install docker compose
sudo curl -L https://github.com/docker/compose/releases/latest/download/docker-compose-$(uname -s)-$(uname -m) -o /usr/local/bin/docker-compose
sudo chmod +x /usr/local/bin/docker-compose
```
- Create certificate
```sh
sudo certbot certonly --standalone -d suad.xyz
# This will create certificate in /etc/letsencrypt/live/suad.xyz/
```

- Run server
```sh
docker-compose up
```
