### OpenSSL

```sh
# Create RSA private/public key, encrypt it with AES and store in private.pem
openssl genrsa -aes256 -out private.pem

# Extract public key, and store it in public.pem
openssl rsa -in private.pem -outform PEM -pubout -out public.pem
```
