#define AGENT_NAME "A1"
#define MAX_HOPS 10
#define SEQUENCE_DELIMETER ";"

#include "../Router/router.h"
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
	while (token != NULL) {
		tokens[(*token_count)++] = token;
		token = strtok(NULL, SEQUENCE_DELIMETER);
	}
	return 0;
}

int
populate_next_agent_hops(char** tokens, char*** agent_hops, int agent_hop_count)
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
		idx++;
	}
	
	return 0;
}

int
process_route_sequence(char* sequence)
{
	int token_count;
	char** tokens = malloc(sizeof(char*)*MAX_HOPS+3);

	if (tokens == NULL) {
		print_error("ROUTER - Failed to malloc tokens");
		return -1;
	}


	if (tokenise_route_sequence(sequence, tokens, &token_count) != 0) {
		print_error("ROUTER - failed to run tokenise_route_sequence routine");
		return -1;
	}

	print_info("ROUTER - Tokenised route sequence");

	int agent_hop_count = atoi(tokens[0]);

	char** next_agent_hops;

	print_info("ROUTER - Populating next agent hops");
	if (populate_next_agent_hops(tokens, &next_agent_hops, agent_hop_count) != 0) {
		print_error("ROUTER - Failed to populate agent hops");
		return -1;
	}	

	printf("[+] ROUTER - Next hop to route: %s\n", next_agent_hops[0]);

	if (find_next_hop(next_agent_hops[0]) != 0) {
		print_error("ROUTER - Failed to find next hop information");
		return -1;
	}

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
