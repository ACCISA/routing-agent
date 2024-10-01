#define AGENT_NAME "A1"
#define MAX_HOPS 10
#define SEQUENCE_DELIMETER ";"

#include "../Router/router.h"
#include "../Message/message.h"
#include "../Utils/utils.h"
#include "../Utils/error.h"

int
is_target(char* agent_name)
{
	return (strncmp(agent_name, AGENT_NAME, strlen(agent_name)) == 0);
}

int
tokenise_route_sequence(char* sequence, char** tokens, int* token_count)
{
	*token_count = 0;

	char* token = strtok(sequence, SEQUENCE_DELIMETER);
	if (token == NULL) {
		print_error("ROUTER - Failed to strtok routing sequence");
		return -1;
	}
	int idx=0;
	while (token != NULL) {
		tokens[(*token_count)++] = token;
		printf("token: %s\n", tokens[idx++]);
		token = strtok(NULL, SEQUENCE_DELIMETER);
	}
	return 0;
}

int
populate_reverse_agent_hops(char** tokens, char*** agent_hops, int agent_hop_count)
{
	*agent_hops = (char**)malloc(sizeof(char*)*agent_hop_count+1);
	
	if (*agent_hops == NULL) {
		print_error("ROUTER - Failed to allocate mem for agen_hops revese");
		return -1;
	}

	int idx = 0;
	for (int i = 1; i < agent_hop_count; i++) {
		(*agent_hops)[idx] = (char*)malloc(sizeof(char)*(strlen(tokens[i])+1));
		if ((*agent_hops)[idx] == NULL) {
			print_error("ROUTER - Failed to allocate mem for agent_hops reverse entry");
			return -1;
		}
		strncpy((*agent_hops)[idx], tokens[i], strlen(tokens[i]));
		(*agent_hops)[idx][strlen(tokens[i])] = '\0';
		printf("rev: %s\n", (*agent_hops)[idx]);
		idx++;
	}

	return 0;
}

int
populate_forward_agent_hops(char** tokens, char*** agent_hops, int agent_hop_count)
{
	*agent_hops = (char**)malloc(sizeof(char*)*agent_hop_count-1);

	if (*agent_hops == NULL) {
		print_error("ROUTER - Failed to allocate mem for agent_hops");
		return -1;
	}
	int idx = 0;
	for (int i = 2; i <= agent_hop_count; i++) {
		(*agent_hops)[idx] = (char*)malloc(sizeof(char)*(strlen(tokens[i])+1));
		if ((*agent_hops)[idx] == NULL) {
			print_error("ROUTEr - Failed to allocate mem for agent_hops entry");
			return -1;
		}
		strncpy((*agent_hops)[idx], tokens[i], strlen(tokens[i]));
		(*agent_hops)[idx][strlen(tokens[i])] = '\0';
		printf("rev: %s\n", (*agent_hops)[idx]);
		idx++;
	}
	
	return 0;
}


char*
build_reverse_route_sequence(char** next_agent_hops, 
			int next_agent_hops_len, 
			int agent_hop_progress,
			char* sender_name,
			int instruction,
			char* msg_id)
{
	char* result = malloc(MAX_ROUTE_SEQUENCE_LEN*sizeof(char)+1);
	char prefix[5];
	char hop_count_str[5];
	char delim[] = ";";
	char instruction_str[5];

	if (result == NULL) {
		print_error("ROUTER - Failed to malloc next reverse route seqeunce");
		return NULL;
	}

	result[0] = '\0';
	sprintf(prefix, "%d;", next_agent_hops_len);
	
	strcat(result, prefix);

	strcat(result, sender_name);
	strcat(result, delim);

	printf("h\n");
	printf("nah: %s\n", next_agent_hops[0]);
	printf("nah: %s\n", next_agent_hops[1]);
	printf("nah: %s\n", next_agent_hops[2]);
	for (int i = 0; i < next_agent_hops_len; i++) {
		strcat(result, next_agent_hops[i]);
		strcat(result, ";");
	}
	
	printf("h\n");
	sprintf(hop_count_str, "%d;", agent_hop_progress);
	strcat(result, hop_count_str);

	sprintf(instruction_str, "%d;", instruction);
	strcat(result, instruction_str);

	strcat(result, msg_id);

}


char*
build_forward_route_sequence(char** next_agent_hops, 
			int next_agent_hops_len,
			int agent_hop_progress,
			int instruction,
			char* msg_id)
{
	char* result = malloc(MAX_ROUTE_SEQUENCE_LEN*sizeof(char)+1);
	char prefix[5];
	char hop_count_str[5];
	char instruction_str[5];

	if (result == NULL) {
		print_error("ROUTER - Failed to malloc next route sequence");
		return NULL;
	}

	result[0] = '\0';

	sprintf(prefix, "%d;", next_agent_hops_len);
	strcat(result, prefix);

	for (int i = 0; i < next_agent_hops_len; i++) {
		strcat(result, next_agent_hops[i]);
		strcat(result, ";");
	}

	sprintf(hop_count_str, "%d;", agent_hop_progress);
	strcat(result, hop_count_str);

	sprintf(instruction_str, "%d;", instruction);
	strcat(result, instruction_str);
	
	strcat(result, msg_id);
	
	return result;
}

int
process_route_sequence(char* sequence)
{
	int token_count;
	peer_t* sender_peer;
	message_t* return_msg;
	int is_forward = 1;
	int orig_sequence_len = strlen(sequence);
	char** tokens = malloc(sizeof(char*)*MAX_HOPS+3);
	if (tokens == NULL) {
		print_error("ROUTER - Failed to malloc tokens");
		return -1;
	}


	if (tokenise_route_sequence(sequence, tokens, &token_count) != 0) {
		print_error("ROUTER - failed to run tokenise_route_sequence routine");
		return -1;
	}

	if (token_count < 5) {
		printf("[!] ROUTER - Routing sequence is missing elements (failed_sequence=%s)\n", sequence);
		return -1;
	}
	int agent_hop_count = atoi(tokens[0]);
	int agent_hop_progress = atoi(tokens[token_count-3]);
	int instruction = atoi(tokens[token_count-2]);
	char* msg_id = tokens[token_count-1];
	char* sender = tokens[1];
	
	if ((return_msg = get_message(msg_id)) != NULL) {
		is_forward = 0;
	}

	print_info("ROUTER - Message info:");
	printf("[+] ROUTER - sender: %s\n", sender);
	if (is_forward == 0) {
		print_info("ROUTER - msg_type: reverse");
	} else {
		print_info("ROUTER - msg_type: forward");
	}
	printf("[+] ROUTER - agent_hop_count: %d\n", agent_hop_count);
	printf("[+] ROUTER - agent_hop_progress: %d\n", agent_hop_progress);
	printf("[+] ROUTER - instruction: %d\n", instruction);
	printf("[+] ROUTER - msg_id: %s\n", msg_id);

	// TODO deal with reverse
	// TODO redo this function, seperate in reverse and forward
	
	if ((sender_peer = find_peer_info(sender)) == NULL) {
		printf("[!] ROUTER - Received sequence from agent not in peer list (sender=%s)\n", sender);
		return -1;
	}

	char** next_agent_hops;

	print_info("ROUTER - Populating next agent hops");

	if (is_forward == 0) {
		if (populate_reverse_agent_hops(tokens, &next_agent_hops, agent_hop_count) != 0) {
			print_error("ROUTER - Failed to populate reverse agent hops");
			return -1;
		}
	} else {
		if (populate_forward_agent_hops(tokens, &next_agent_hops, agent_hop_count) != 0) {
			print_error("ROUTER - Failed to populate forward agent hops");
			return -1;
		}
	}

	int removed_len = strlen(tokens[1]);

	printf("[+] ROUTER - Next hop to route through: %s\n", next_agent_hops[0]);
	
	peer_t* next_peer;

	if ((next_peer = find_peer_info(sender)) == NULL) {
		print_error("ROUTER - Failed to find next hop information");
		return -1;
	}
	
	char* new_route_sequence = NULL;

	if (is_forward == 1) {
		new_route_sequence = build_forward_route_sequence(next_agent_hops, agent_hop_count-1,
				agent_hop_progress+1,
				instruction,
				msg_id);
	} else {
		new_route_sequence = build_reverse_route_sequence(next_agent_hops, agent_hop_count+1,
				agent_hop_progress+1,
				return_msg->sender->agent_name,
				instruction,
				msg_id);
	}

	if (new_route_sequence == NULL) {
		print_error("ROUTER - Failed to build new route sequence");
		return -1;
	}


	printf("[+] ROUTER - New forward route sequence (sequence=%s)\n", new_route_sequence);
	
	message_t* msg = create_message(msg_id, next_peer);
	store_message(msg);
	display_message_store();
	return 0;
}

char*
update_route_sequence(char* sequence)
{
	char* updated_sequence;
}


void
forward_next_hop(char* sequence)
{

}

void
forward_next_instruction(char* instruction)
{

}

void
read_routing_section(char* ecrypted_section_sequence, int enc_sequence_len, int is_forward, char* msg_id)
{

	char section_sequence[30];

	if (AES_decrypt(encrypted_section_sequence, enc_sequence_len, Agent->key, Agent->iv, section_sequence) == 1) {
		print_error("ROUTER - Failed to decrypt encrypted routing sequence");
		return;
	}

	char* prev_agent_name = strtok(section_sequence, ",");
	char* cur_agent_name = strtok(NULL, ",");
	char* next_agent_name = strtok(NULL, ",");

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

	if (strcmp(Agent->agent_name, cur_agent_name, strlen(cur_agent_name)) != 0) {
		print_error("ROUTER - Failed to validate cur_agent_name from global variable");
		return;
	}

	if (is_forward == 1) {
		message_t* new_msg = create_message(msg_id, prev_peer);
		store_message(new_msg);
		//ASYNC_add_job(send_tcp_message, send_tcp_message_cb);
	} else {
		message_t* prev_msg = get_message(msg_id);

		if (prev_msg == NULL) {
			print_error("ROUTER - Failed to find stored message of reverse routing sequence");
			return;
		}

		if (strcmp(prev_msg->sender, prev_peer->agent_name, strlen(prev_peer->agent_name)) != 0) {
			print_error("ROUTER - Failed to validate message, prev_peer != msg_peer");
			return;
		}

		//ASYNC_add_job(send_tcp_message, send_tcp_message_cb);
	}

}

void
process_route_sequence(rheader_t* routing_header, rpayload_t* routing_payload)
{
	if (routing_header->is_destination) {
		print_info("ROUTER - Message arrived at destination, instruction added to queue");
		return process_instruction(routing_header, routing_payload);
	}

	read_routing_section(routing_payload->sections[routing_header->cur_section]);

	routing_header->cur_section += 1;

	if (routing_header->num_sections == routing_header->cur_sections) { 
		routing_header->is_destination = 1;
		return;
	}

}
