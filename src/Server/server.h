#ifndef SERVER_H_
#define SERVER_H_

#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ssl.h>

typedef struct server {
	int sockfd;
	SSL_CTX* ctx;
} server_t;

typedef struct connection {
	int clientfd;
	SSL* ssl;
} connection_t;

void init_openssl(void);
void cleanup_openssl(void);
SSL_CTX* create_ssl_context(void);
void configure_ssl_context(SSL_CTX* ctx);
server_t* create_server_struct(void);
int create_socket(const char* hostname, int port);
SSL* create_ssl_connection(const char* hostname, int port);

int accept_client_connection(void* data);
int accept_client_connection_cb(void* data);
int read_routing_data(void* data);
int read_routing_data_cb(void* data);
int send_routing_data(void* data);
int send_routing_data_cb(void* data);

#endif
