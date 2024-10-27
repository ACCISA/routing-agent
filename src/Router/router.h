#ifndef ROUTER_H_
#define ROUTER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct peer {
	char* ip_addr;
	int port;
	char* agent_name;
	struct peer* next_peer;
} peer_t;

typedef struct routing {
	int size;
	peer_t* table;
} routing_t;


typedef struct RoutingHeader {
	int8_t		is_destination;
	int8_t 		is_forward;
	int8_t 		has_response;
	int32_t 	num_sections;
	int32_t 	cur_section;
	int32_t 	response_len;
	int32_t		msg_id;
	int32_t* 	sections_len;
} rheader_t;

typedef struct RoutingPayload {
	char** 	sections;
	char*	response;
} rpayload_t;

typedef struct RoutingMessage {
	rheader_t* 	routing_header;
	rpayload_t* 	routing_payload;
	peer_t*		peer;
} rmessage_t;

typedef struct RoutingBuffer {
	rheader_t* 	routing_header;
	rpayload_t*	routing_payload;
} rbuffer_t;


void display_header_info(rheader_t* routing_header);
int parse_routing_message(unsigned char* data, int data_len, unsigned char* header_data, int* header_len, unsigned char* payload_data, int* payload_len);
rheader_t* create_routing_header(unsigned char* data);
rpayload_t* create_routing_payload(unsigned char* data, int32_t num_sections, int32_t* sections_len);

void free_routing_message(rmessage_t* routing_message);
void read_routing_seection(unsigned char* encrypted_section_sequence, int enc_sequence_len, int is_forward, char* msg_id);
int process_route_sequence(rheader_t* routing_header, rpayload_t* routing_payload);
int process_instruction(rheader_t* routing_header, rpayload_t* routing_payload);


void display_peer_info(peer_t* peer);
void display_peer_table(void);
void add_peer_entry(peer_t* new_peer);
peer_t* create_peer_entry(char* ip_addr, int port, char* agent_name);
peer_t* remove_peer_entry(char* agent_name);
peer_t* find_peer_info(char* agent_name);

#endif
