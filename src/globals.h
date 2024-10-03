#ifndef GLOBAL_H
#define GLOBAL_H

#include "Queue/queue.h"

#define MAX_ROUTE_SEQUENCE_LEN 100

typedef struct peer {
	char* ip_addr;
	int port;
	char* agent_name;
	struct peer* next_peer;
} peer_t;

typedef struct message {
	int32_t id;
	char* time_sent;
	peer_t* sender;
	struct message* next_msg;
} message_t;

typedef struct message_store {
	int size;
	message_t* msg;
} msg_store_t;

typedef struct routing {
	int size;
	peer_t* table;
} routing_t;

typedef struct {
	char* agent_name;
	int port;
	char* ip_addr;
	unsigned char* iv;
	unsigned char* decrypt_key;
	routing_t* routing;
	msg_store_t* msg_store;
	rqueue_t* reactor_queue;
} AgentInfo;


extern AgentInfo* Agent;

void initialize_agent_info(void);
int is_agent_init(void);
void set_agent_name(char* name);
void set_agent_ip_addr(char* ip_addr);
void set_agent_peer_table(routing_t* peer_table);
void set_agent_port(int port);
void set_agent_key(unsigned char* decrypt_key);
void set_agent_iv(unsigned char* iv);
void display_agent_info(void);

#endif
