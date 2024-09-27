#define AGENT_NAME "Agent1"

#include "../Router/router.h"

int
is_target(char* agent_name)
{
	return strncmp(agent_name, AGENT_NAME, strlen()) == 0
}

void
process_route_sequence(char* sequence)
{

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
