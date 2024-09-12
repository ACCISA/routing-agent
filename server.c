#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#include "router.h"

void
process_instruction(message_t* msg)
{
	// TODO
	if (msg->instruction == 1) {
		// route instruction to next hop
		printf("Routing instruction");
	}
	if (msg->instruction == 2) {
		char hostname[100];

		if (gethostname(hostname, sizeof(hostname)) != 0) {
			printf("Failed to get hostname");
			return;
		}
		printf("hostname: %s\n", hostname);
		printf("Sending response back to id: %d\n", msg->source);
		entry_t* entry = find_next_hop(routing_table,msg->source);
		forward_next_hop(entry, 3, source, hostname);
	}
	if (msg->instruction == 3) {
		printf("Action response: %s\n", msg->data);
	}	

}

void
start_listener(int port)
{
	int server_fd, new_socket;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	int instruction;
	int valread;
	message_t* msg;
	
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		printf("Failed to create server socket\n");
		return;
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		printf("Failed to bind to socket\n");
		return;
	}
	
	if (listen(server_fd, 3) < 0) {
		printf("Failed to listen\n");
		return;
	}
	
	printf("Server listening\n");

	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
		printf("Accept failed\n");
		return;
	}

	valread = read(new_socket, msg, sizeof(msg));
	if (valread < 0) {
		printf("Failed to read instruction\n");
		return;
	} else {
		printf("Received instruction: %d\n", msg->instruction);
		process_instruction(msg);
	}
	
	close(new_socket);
	close(server_fd);
	
	return;
}

void
send_response(void)
{

}

