#ifndef ROUTER_H
#define ROUTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../globals.h"

int tokenise_route_sequence(char* sequence, char** tokens, int* token_count);
int populate_next_agent_hops(char** tokens, char*** agent_hops, int agent_hop_count);
int find_next_hop(char* next_agent);
int  process_route_sequence(char* sequence);
char* update_route_sequence(char* sequence);
void forward_next_hop(char *sequence);
void forward_instruction(char* instruction);
int is_target(char* agent_name);

void display_peer_info(peer_t* peer);
void add_peer_entry(peer_t* new_peer);
peer_t* create_peer_entry(char* ip_addr, int port, char* agent_name);
peer_t* remove_peer_entry(char* agent_name);
peer_t* find_peer_info(char* agent_name);

#endif
