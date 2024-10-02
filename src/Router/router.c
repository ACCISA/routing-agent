#define AGENT_NAME "A1"
#define MAX_HOPS 10
#define SEQUENCE_DELIMETER ";"

#include "../Router/router.h"
#include "../Message/message.h"
#include "../Utils/utils.h"
#include "../Utils/error.h"

void
read_routing_section(char* encrypted_section_sequence, int enc_sequence_len, int is_forward, char* msg_id)
{

	char section_sequence[30];

	if (AES_decrypt(encrypted_section_sequence, enc_sequence_len, Agent->key, Agent->iv, section_sequence) == 1) {
		print_error("ROUTER - Failed to decrypt encrypted routing sequence");
		return;
	}

	char* prev_agent_name = strtok(section_sequence, ",");
	char* cur_agent_name = strtok(NULL, ",");
	char* next_agent_name = strtok(NULL, ",");
	
	if (prev_agent_name == NULL || cur_agent_name == NULL || next_agent_name == NULL) {
		print_error("ROUTER - Failed to tokenise section");
		return;
	}

	peer_t* prev_peer;
	peer_t* next_peer;

	if ((prev_peer = find_peer_info(prev_agent_name)) == NULL) {
		print_error("ROUTER - Failed to find prev peer from routing sequence");
		return;
	}

	if ((next_peer = find_peer_info(next_agent_name)) == NULL) {
		print_error("ROUTER - Failed to find next peer from routing sequence");
		return;
	}

	if (strncmp(Agent->agent_name, cur_agent_name, strlen(cur_agent_name)) != 0) {
		print_error("ROUTER - Failed to validate cur_agent_name from global variable");
		return;
	}

	if (is_forward == 1) {
		message_t* new_msg = create_message(msg_id, prev_peer);
		store_message(new_msg);
		// REACTOR_add_job(send_tcp_message, send_tcp_message_cb, );

	} else {
		message_t* prev_msg = get_message(msg_id);

		if (prev_msg == NULL) {
			print_error("ROUTER - Failed to find stored message of reverse routing sequence");
			return;
		}

		if (strncmp(prev_msg->sender, prev_peer->agent_name, strlen(prev_peer->agent_name)) != 0) {
			print_error("ROUTER - Failed to validate message, prev_peer != msg_peer");
			return;
		}

		// REACTOR_add_job(send_tcp_message, send_tcp_message_cb);
	}

}

int
process_route_sequence(rheader_t* routing_header, rpayload_t* routing_payload)
{
	if (routing_header->is_destination) {
		print_info("ROUTER - Message arrived at destination, instruction added to queue");
		return process_instruction(routing_header, routing_payload);
	}

	read_routing_section(routing_payload->sections[routing_header->cur_section],
			routing_header->sections_len[routing_header->cur_section],
		       	routing_header->is_forward, routing_header->msg_id);

	routing_header->cur_section += 1;

	if (routing_header->num_sections == routing_header->cur_section) routing_header->is_destination = 1;

	return 0;
}
