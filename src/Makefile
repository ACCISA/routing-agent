CC := gcc
CFLAGS := -Wall
SRC := main.c globals.c Router/*.c Instructor/*.c Server/*.c Message/*.c Reactor/*.c Crypt/*.c Utils/*.c Queue/*.c Config/*.c
TARGET := main

PASSPHRASE=123
DAYS_VALID=365
KEY_FILE=key.pem
CERT_FILE=cert.pem
CSR_FILE=csr.pem

all:
	@echo "Generating private key (with passphrase)..."
	openssl genpkey -algorithm RSA -out $(KEY_FILE) -aes256 -pass pass:$(PASSPHRASE)
	@echo "Generating CSR..."
	openssl req -new -key $(KEY_FILE) -out $(CSR_FILE) -passin pass:$(PASSPHRASE) -subj "/C=US/ST=State/L=City/O=Organization/CN=example.com"
	@echo "Generating self-signed certificate..."
	openssl x509 -req -days $(DAYS_VALID) -in $(CSR_FILE) -signkey $(KEY_FILE) -out $(CERT_FILE) -passin pass:$(PASSPHRASE)
	@echo "Cleaning up CSR..."
	rm -f $(CSR_FILE)
	$(CC) $(CFLAGS) $(SRC) -lssl -lcrypto -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean

