#include "../Server/server.h"
#include "../Router/router.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <poll.h>

void
init_openssl(void)
{
	SSL_load_error_strings();
	OpenSSL_add_ssl_algorithms();
}

void
cleanup_openssl(void)
{
	EVP_cleanup();
}

SSL_CTX*
create_ssl_context(void)
{
	const SSL_METHOD* method;
	SSL_CTX *ctx;

	method = SSLv23_client_method();

	ctx = SSL_CTX_new(method);
	if (!ctx) {
		print_error("Unable to create SSL context");
		ERR_print_errors_fp(stderr);
		return NULL;
	}

	return ctx;
}

void
configure_ssl_context(SSL_CTX* ctx)
{
	if (SSL_CTX_use_certificate_file(ctx, "cert.pem", SSL_FILETYPE_PEM) <= 0) {
		ERR_print_errors_fp(stderr);
		return;
	}

	if (SSL_CTX_use_PrivateKey_file(ctx, "key.pem", SSL_FILETYPE_PEM) <= 0) {
		ERR_print_errors_fp(stderr);
		return;
	}
}

int
create_server_socket()
{
	int sockfd, newsockfd;
	struct sockaddr_in addr;
	SSL_CTX* ctx;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		print_error("SERVER - Failed to create server socket");
		return -1;
	}

	addr.sin_family 	= AF_INET;
	addr.sin_port   	= htons(Agent->port);
	addr.sin_addr.s_addr 	= INADDR_ANY;

	if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		print_error("SERVER - Unable to bind");
		return -1;
	}

	if (listen(sockfd, 1) < 0) {
		print_error("SERVER - Failed to listen");
	}
	
	return sockfd;
}

int
create_socket(const char* hostname, int port)
{
	int sock;
	struct sockaddr_in  addr;

	sock  = socket(AF_INET, SOCK_STREAM, 0);
	if (sock <  0) {
		print_error("Unable to create socket");
		return -1;
	}

	memset(&addr, 0, sizeof(addr));
    	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	if (inet_pton(AF_INET, hostname, &addr.sin_addr) <= 0) {
		print_error("Invalid hostname/address");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		print_error("Failed to connect to agent");
		return -1;
	}

	return sock;
}

SSL*
create_ssl_connection(const char* hostname, int port)
{
	int sock;
	SSL_CTX *ctx;
	SSL *ssl;

	init_openssl();
	ctx = create_ssl_context();

	sock = create_socket(hostname, port);

	ssl = SSL_new(ctx);
	SSL_set_fd(ssl, sock);

	if (SSL_connect(ssl) <= 0) {
		ERR_print_errors_fp(stderr);
		return NULL;
	}

	print_info("Connected with encryption:");
	printf("[+] SERVER - alg_enc: %s\n", SSL_get_cipher(ssl));
	
	rhandler_t* handler = (rhandler_t*)malloc(sizeof(rhandler_t));

	handler->event_handler 		= send_routing_data;
	handler->event_handler_cb 	= send_routing_data_cb;
	handler->data 			= NULL;
	handler->next_handler 		= NULL;

	REACTOR_register_handler(handler);

	return ssl;
}

int
read_routing_data(void* data)
{

}

int
read_routing_data_cb(void* data)
{

}

int
send_routing_data(void* data)
{
	unsigned char buffer[300];

	rmessage_t* routing_message = (rmessage_t*)data;

	if (routing_message == NULL) {
		print_error("SERVER - Failed to cast data to rmessage_t");
		return 1;
	}

	rbuffer_t* routing_buffer = (rbuffer_t*)malloc(sizeof(rbuffer_t));

	routing_buffer->routing_header = routing_message->routing_header;
	routing_buffer->routing_payload = routing_message->routing_payload;

	SSL* ssl = create_ssl_connection(routing_message->peer->ip_addr, routing_message->peer->ip_addr);

	if (ssl == NULL) {
		return 1;
	}

	memcpy(routing_buffer, buffer, sizeof(routing_buffer));

	printf("[+] SERVER - Sending %d bytes\n", sizeof(routing_buffer));

	if (SSL_write(ssl, buffer, sizeof(routing_buffer)) <= 0) {
		ERR_print_errors_fp(stderr);
	}

}

int
send_routing_data_cb(void* data)
{
	rmessage_t* routing_message = (rmessage_t*)data;

	free_routing_message(routing_message);

	return 0;
}
