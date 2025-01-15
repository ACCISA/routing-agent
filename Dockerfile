FROM gcc:latest

ENV PASSPHRASE=123
ENV DAYS_VALID=365
ENV KEY_FILE=src/key.pem
ENV CERT_FILE=src/cert.pem
ENV CSR_FILE=src/csr.pem

RUN apt-get update && apt-get install -y libssl-dev openssl net-tools iproute2

COPY . .

RUN openssl genpkey -algorithm RSA -out $KEY_FILE -aes256 -pass pass:$PASSPHRASE && \
    openssl req -new -key $KEY_FILE -out $CSR_FILE -passin pass:$PASSPHRASE -subj "/C=US/ST=State/L=City/O=Organization/CN=example.com" && \
    openssl x509 -req -days $DAYS_VALID -in $CSR_FILE -signkey $KEY_FILE -out $CERT_FILE -passin pass:$PASSPHRASE && \
    rm -f $CSR_FILE

WORKDIR src
RUN make

EXPOSE 2222

CMD ["/bin/bash"]

