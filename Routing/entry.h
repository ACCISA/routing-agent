#ifndef ROUTER_H
#define ROUTER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct entry {
	struct entry* next_entry;
	int destination;
	int next_hop;
	int port;
	char* ip_addr;
} entry_t;

void add_route_entry(entry_t** entry_head, entry_t* new_entry);
void remove_tail_entry(entry_t* entry_head);
entry_t* create_route_entry(int destination, int next_hop, char* ip_addr, int port);

#endif
