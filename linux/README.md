### Permissions
```sh
# Give all permissions to ower and only read for all other users
# For more see https://chmod-calculator.com
chmod 744 my file
```

### OpenSSL

```sh
# Create RSA private/public key, encrypt it with AES and store in private.pem
openssl genrsa -aes256 -out private.pem

# Extract public key, and store it in public.pem
openssl rsa -in private.pem -outform PEM -pubout -out public.pem

# Create Self Signed Certificate
# Root and custom certificates location
cd /etc/ssl

openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem -sha256 -days 3650
```
