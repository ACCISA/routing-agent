#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../globals.h"

message_t* create_message(char* id, peer_t* sender);
void display_message_info(message_t* msg);
void display_message_store(void);
void store_message(message_t* msg);
message_t* get_message(char* msg_id);
char* int_id_to_str(int msg_id);
message_t* remove_message(char* msg_id);

