#ifndef SERVER_H
#define SERVER_H

#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ssl.h>

void init_openssl(void);
void cleanup_openssl(void);
SSL_CTX* create_ssl_context(void);
void configure_ssl_context(SSL_CTX* ctx);
int create_server_socket(void);
int create_socket(const char* hostname, int port);
SSL* create_ssl_connection(const char* hostname, int port);
int read_routing_data(void* data);
int read_routing_data_cb(void* data);
int send_routing_data(void* data);
int send_routing_data_cb(void* data);

#endif
