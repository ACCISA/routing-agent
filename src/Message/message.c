#include "../Message/message.h"
#include "../Queue/queue.h"
#include "../Reactor/reactor.h"
#include "../Router/router.h"
#include "../globals.h"

message_t*
create_message(int32_t id, peer_t* sender)
{
	time_t cur_time;
	time(&cur_time);
	struct tm* cur_time_h = localtime(&cur_time);
	char time_sent[100];
	strftime(time_sent, sizeof(time_sent), "%Y-%m-%d %H:%M:%S", cur_time_h);

	message_t* msg = (message_t*)malloc(sizeof(message_t));
	msg->id = id;
	msg->time_sent = (char*)malloc(sizeof(char)*strlen(time_sent)+1);
	strncpy(msg->time_sent, time_sent, strlen(time_sent));
	msg->time_sent[strlen(time_sent)] = '\0';
	msg->sender = sender;
	msg->next_msg = NULL;

	printf("[+] MESSAGE - Create message (time=%s)\n", time_sent);
	return msg;
}

void
display_message_info(message_t* msg)
{
	printf("[+] MESSAE - msg_id: %d, time_sent: %s, sender: %s\n",
			(msg->id),
			msg->time_sent,
			msg->sender->agent_name);
}

void
display_message_store(void)
{
	printf("-----------------------------------------------\n");
	if (is_agent_init() == 0) return;

	message_t* temp_msg = Agent->msg_store->msg;
	printf("[+] MESSAGE - Displaying message store of size: %d\n", Agent->msg_store->size);

	while (temp_msg != NULL) {
		display_message_info(temp_msg);
		temp_msg = temp_msg->next_msg;
	}
	printf("-----------------------------------------------\n");
}

void
store_message(message_t* msg) 
{
	if (is_agent_init() == 0) return;

	printf("[+] MESSAGE - New message added to store, msg_id: %d\n",msg->id);
	
	if (Agent->msg_store->size == 0) {
		Agent->msg_store->msg = msg;
		Agent->msg_store->size++;
		return;
	}

	msg->next_msg = Agent->msg_store->msg;
	Agent->msg_store->msg = msg;
	Agent->msg_store->size++;

}

message_t*
get_message(int32_t msg_id)
{
	if (Agent->msg_store->size == 0) {
		printf("[!] MESSAGE - Failed to find (msg_id=%d) in message store\n", msg_id);
		return NULL;
	}

	message_t* found_msg = Agent->msg_store->msg;

	while (found_msg != NULL) {
		if (found_msg->id == msg_id) {
			printf("[+] MESSAGE - Found entry for msg_id: %d\n", msg_id);
			return found_msg;
		}
		found_msg = found_msg->next_msg;
	}
	printf("[!] MESSAGE - Failed to find (msg_id=%d) in message store\n", msg_id);
	return NULL;
}

message_t*
remove_message(int32_t  msg_id)
{
	if (is_agent_init() == 0) return NULL;
	if (Agent->msg_store->size == 0) return NULL;

	message_t* temp_msg = Agent->msg_store->msg;
	message_t* prev_msg = NULL;
	message_t* removed_msg;

	while (temp_msg != NULL) {
		if (temp_msg->id == msg_id) {
			printf("[+] MESSAGE - Removed message (msg_id=%d) from message store\n", msg_id);
			if (prev_msg == NULL) {
				removed_msg = Agent->msg_store->msg;
				Agent->msg_store->msg = Agent->msg_store->msg->next_msg;
				Agent->msg_store->size--;
				return removed_msg;
			}
			
			removed_msg = temp_msg;
			printf("data loss\n");
			prev_msg->next_msg = temp_msg->next_msg;
			Agent->msg_store->size--;
			return removed_msg;
		}
		prev_msg = temp_msg;
		temp_msg = temp_msg->next_msg;
	}
	
	printf("[!] ROUTER - Unable to remove message (msg_id=%d)\n", msg_id);
	return NULL;
}
