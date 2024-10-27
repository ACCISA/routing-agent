#include "../Router/router.h"
#include "../Reactor/reactor.h"
#include "../Queue/queue.h"
#include "../Message/message.h"
#include "../Crypt/crypt.h"
#include "../Utils/utils.h"
#include "../Utils/error.h"
#include "../Server/server.h"
#include "../globals.h"

void
free_routing_message(rmessage_t* routing_message)
{
	
	for (int i = 0; i < routing_message->routing_header->num_sections; i++) {
		free(routing_message->routing_payload->sections[i]);
	}
		
	if (routing_message->routing_header->has_response) {
		free(routing_message->routing_payload->response);
	}

	free(routing_message->routing_header->sections_len);
	free(routing_message->routing_header);
	
	free(routing_message->routing_payload);
}
void
read_routing_section(rheader_t* routing_header, rpayload_t* routing_payload)
{
	unsigned char* encrypted_section_sequence = (unsigned char*)routing_payload->sections[routing_header->cur_section-1];
	int enc_sequence_len = routing_header->sections_len[routing_header->cur_section-1];
	int is_forward = routing_header->is_forward;
	int32_t msg_id = routing_header->msg_id;
	unsigned char section_sequence[30];
	int data_len = 0;
	if ((data_len = AES_decrypt(encrypted_section_sequence, enc_sequence_len, 
					Agent->decrypt_key,
					Agent->iv,
					section_sequence)) == 1) {
		print_error("ROUTER - Failed to decrypt encrypted routing sequence");
		return;
	}

	section_sequence[data_len] = '\0';
	printf("[+] ROUTER - Decrypted routing sequence: %s\n", section_sequence);

	char* prev_agent_name = strtok((char*)section_sequence, ",");
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
		routing_header->cur_section += 1;

		if (routing_header->num_sections == routing_header->cur_section) {
			print_info("ROUTER - Next hop is destination");
			routing_header->is_destination = 1;
			routing_header->is_forward = 0;
		}

		rmessage_t* routing_message = (rmessage_t*)malloc(sizeof(rmessage_t));
		
		routing_message->routing_header  = routing_header;
		routing_message->routing_payload = routing_payload;
		routing_message->peer  		 = next_peer;



		REACTOR_add_job(send_routing_data, send_routing_data_cb, (void*)routing_message);
	} else {
		message_t* prev_msg = remove_message(msg_id);

		if (prev_msg == NULL) {
			print_error("ROUTER - Failed to find stored message of reverse routing sequence");
			return;
		}

		if (strncmp(prev_msg->sender->agent_name, prev_peer->agent_name, strlen(prev_peer->agent_name)) != 0) {
			print_error("ROUTER - Failed to validate message, prev_peer != msg_peer");
			return;
		}

		routing_header->cur_section -= 1;
		
		rmessage_t* routing_message = (rmessage_t*)malloc(sizeof(rmessage_t));

		routing_message->routing_header  = routing_header;
		routing_message->routing_payload = routing_payload;
		routing_message->peer 		 = prev_peer;

		// REACTOR_add_job(send_tcp_message, send_tcp_message_cb, (void*)routing_message, (void*)routing_message);
	}

}

int
process_instruction(rheader_t* routing_header, rpayload_t* routing_payload)
{
	print_info("ROUTER - Added instruction to reactor queue");
	// TODO process instruction and add to reactor queue
	// REACTOR_add_job(do_instruction, do_instruction_cb, , );
	return 0;
}

int
process_route_sequence(rheader_t* routing_header, rpayload_t* routing_payload)
{
	if (routing_header->is_destination) {
		print_info("ROUTER - Message arrived at destination, instruction added to queue");
		return process_instruction(routing_header, routing_payload);
	}

	read_routing_section(routing_header, routing_payload);

	return 0;
}
