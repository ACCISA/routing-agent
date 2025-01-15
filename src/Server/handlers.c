#include "../Reactor/reactor.h"
#include "../Server/server.h"
#include "../Utils/utils.h"
#include "../Message/message.h"
#include "../Router/router.h"
#include "../Instructor/task.h"
#include "../globals.h"

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

//TODO error handling
int
read_routing_data(void* data)
{
	int header_len;
	int payload_len;
	unsigned char* header;
	unsigned char* payload;
	rheader_t* routing_header;
	rpayload_t* routing_payload;


	connection_t* connection = (connection_t*) data;
	if (SSL_accept(connection->ssl) <= 0) {
		print_error("SERVER - Failed to perform ssl handshake");
		close(connection->clientfd);
		REACTOR_unregister_handler(connection->clientfd);
		free(connection);
		return -1;
	}


	char buffer[2000];
	int bytes;
	
	bytes = SSL_read(connection->ssl, buffer, sizeof(buffer)-1);
	if (bytes > 0) {
		buffer[bytes] = 0;
		printf("size: %d\n", bytes);
		printf("sizeof: %d\n", sizeof(buffer)-1);
		print_hex(buffer, bytes);
	}
	
	header = (unsigned char*)malloc(sizeof(unsigned char)*50);
	payload = (unsigned char*)malloc(sizeof(unsigned char)*50);

	if (parse_routing_message(buffer, bytes, header, &header_len, payload, &payload_len) == -1) {
		print_error("SERVER - Failed to create header buffer");
		close(connection->clientfd);
		REACTOR_unregister_handler(connection->clientfd);
		free(header);
		free(payload);
		return -1;
	}	

	printf("h_len: %d\n", header_len);
	print_hex(header, header_len);
	printf("p_len: %d\n", payload_len);
	print_hex(payload, payload_len);

	if ((routing_header = create_routing_header(header)) == NULL) {
		print_error("SERVER - Failed to create routing header");
		close(connection->clientfd);
		REACTOR_unregister_handler(connection->clientfd);
		free(header);
		free(payload);
		return -1;	
	}

	if ((routing_payload = create_routing_payload(payload, routing_header->num_sections, routing_header->sections_len)) == NULL) {
		close(connection->clientfd);
		REACTOR_unregister_handler(connection->clientfd);
		print_error("SERVER - Failed to create routing payload");
		free(header);
		free(payload);
		return -1;
	}
	
	display_header_info(routing_header);

	process_route_sequence(routing_header, routing_payload, connection);

}

int
read_routing_data_cb(void* data)
{

}

int
send_instruction_response_cb(void* data)
{
	task_t* task = (task_t*)data;

	printf("host: %s\n", task->result);

	SSL_write(task->connection->ssl, (const char*)task->result, strlen(task->result));
	SSL_shutdown(task->connection->ssl);
	SSL_free(task->connection->ssl);
	close(task->connection->clientfd);
	REACTOR_unregister_handler(task->connection->clientfd);
	free(task);
	task = NULL;
}
