#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "../Router/router.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

message_t* create_message(int32_t id, peer_t* sender);
void display_message_info(message_t* msg);
void display_message_store(void);
void store_message(message_t* msg);
message_t* get_message(int32_t msg_id);
message_t* remove_message(int32_t msg_id);

#endif
