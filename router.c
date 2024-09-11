#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "router.h"

// the routing table is a linked list where each node has a destination and next hop

void
add_route_entry(entry_t** entry_head, entry_t* new_entry)
{
	printf("Added new routing entry\n");
	new_entry->next_entry = *entry_head;
	*entry_head = new_entry;

}

entry_t*
create_route_entry(int destination, int next_hop, char* ip_addr, int port)
{
	entry_t* newEntry = (entry_t*)malloc(sizeof(entry_t));
	newEntry->destination = destination;
	newEntry->next_hop = next_hop;
	newEntry->ip_addr = ip_addr;
	newEntry->port = port;
	newEntry->next_entry = NULL;

	return newEntry;
}

void
display_route_table(entry_t* entry_head)
{
	printf("Route Table: \n");
	if (entry_head == NULL) return;
	entry_t* entry_temp = entry_head;
	while (entry_temp != NULL) {
		printf("dst: %d,hop: %d,ip_addr: %s,port: %d\n",
				entry_temp->destination,
				entry_temp->next_hop,
				entry_temp->ip_addr,
				entry_temp->port);

		entry_temp = entry_temp->next_entry;
	}

}

entry_t*
find_next_hop(entry_t* entry_head, int destination)
{
	if (entry_head == NULL) return NULL;

	entry_t* entry_temp = entry_head;
	int idx = 0;
	while (entry_temp != NULL) {

		if (entry_temp->destination == destination && entry_temp->next_hop != 0) {
			printf("Entry #%d, Next Hop: %d\n",
					idx,
					entry_temp->next_hop);
			return entry_temp;
		}	
		
		if (entry_temp->destination == destination && entry_temp->next_hop == 0) {
			printf("Arrived to Destination\n");
			return NULL;
		}

		idx++;
		entry_temp = entry_temp->next_entry;
	}

	return NULL;
}

void
forward_next_hop(entry_t* entry, int instruction)
{
	message_t* msg = (message_t*)malloc(sizeof(message_t));
	msg->instruction = instruction;
	msg->destination = entry->destination;

	int sock;
	struct sockaddr_in server_addr;
	
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Failed to create socket\n");
		return;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(entry->port);

	if (inet_pton(AF_INET, entry->ip_addr, &server_addr.sin_addr) <= 0) {
		printf("Invalid agent address %s, FAIL\n", entry->ip_addr);
		printf("dst %d\n",entry->destination);
		return;
	}

	printf("Trying to connect to %s:%d\n",
			entry->ip_addr,
			entry->port);

	if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		printf("Connection to agent failed\n");
		return;
	}
	
	printf("Connected to agent\n");

	if (send(sock, &msg, sizeof(msg), 0) < 0) {
		printf("Failed to send instruction to agent\n");
		return;
	}

	printf("Instruction sent to agent\n");

	close(sock);

	return;

}

void
main(int argc, char *argv[])
{
	if (argc != 3) {
		printf("missing arguments");
		return;
	}

	int port = atoi(argv[1]);
	char *config_file = argv[2];

	entry_t* entry = read_config(config_file);
	
	if (entry == NULL) {
		printf("Failed to read config file\n");
		return;
	}
	
	entry_t* next_entry = find_next_hop(entry, 2);
	forward_next_hop(next_entry, 1);

	start_listener(port);

}
