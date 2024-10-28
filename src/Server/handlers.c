#include "../Reactor/reactor.h"
#include "../Server/server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <poll.h>

int
accept_client_connection(void* data)
{
	int clientfd;
	struct sockaddr_in client;
	SSL* ssl;

	socklen_t client_len = sizeof(client);
	server_t* server = (server_t*)data;

	if ((clientfd = accept(server->sockfd, (struct sockaddr*)&client, &client_len)) < 0) {
		print_error("SERVER - Failed to accept client connection");
		return -1;
	}

	ssl = SSL_new(server->ctx);
	SSL_set_fd(ssl, clientfd);

	struct pollfd fd;
	fd.fd = clientfd;
	fd.events = POLLRDNORM;

	connection_t* connection = (connection_t*)malloc(sizeof(connection_t));
	connection->clientfd = clientfd;
	connection->ssl = ssl;

	rhandler_t* handler = (rhandler_t*)malloc(sizeof(rhandler_t));

	handler->fd = fd;
	handler->event_handler = read_routing_data;
	handler->event_handler_cb = read_routing_data_cb;
	handler->data = connection;
	handler->next_handler = NULL;

	REACTOR_register_handler(handler);
	return 0;
}

int
accept_client_connection_cb(void* data)
{
	printf("CB called for accept_client_connection_cb\n");
	return 0;
}

int
read_routing_data(void* data)
{
	connection_t* connection = (connection_t*) data;
	if (SSL_accept(connection->ssl) <= 0) {
		print_error("SERVER - Failed to perform ssl handshake");
		return -1;
	}


	char buffer[2000];
	int bytes;
	
	bytes = SSL_read(connection->ssl, buffer, sizeof(buffer)-1);
	if (bytes > 0) {
		buffer[bytes] = 0;
		printf("gotten: %s\n", buffer);
		SSL_write(connection->ssl, "HELLO", strlen("HELLO"));
	}
	SSL_shutdown(connection->ssl);
	SSL_free(connection->ssl);
	close(connection->clientfd);
	exit(0);
}

int
read_routing_data_cb(void* data)
{

}
