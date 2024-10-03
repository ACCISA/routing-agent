#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../globals.h"

message_t* create_message(int32_t id, peer_t* sender);
void display_message_info(message_t* msg);
void display_message_store(void);
void store_message(message_t* msg);
message_t* get_message(int32_t msg_id);
message_t* remove_message(int32_t msg_id);

