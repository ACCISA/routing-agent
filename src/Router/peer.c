#include "../Router/router.h"
#include "../Reactor/reactor.h"
#include "../Message/message.h"
#include "../Queue/queue.h"
#include "../Utils/utils.h"
#include "../Utils/error.h"
#include "../Instructor/task.h"
#include "../Instructor/commands.h"
#include "../globals.h"


void
display_peer_info(peer_t* peer)
{
	print_info("ROUTER - Peer info:");
	printf("[+] agent_name: %s\n", peer->agent_name);
	printf("[+] ip_addr: %s\n", peer->ip_addr);
	printf("[+] port: %d\n", peer->port);
}

void
display_peer_table(void)
{	
	printf("-----------------------------------------------\n");
	if (is_agent_init() == 0) return;

	peer_t* temp_peer = Agent->routing->table;

	printf("[+] ROUTER - Displaying peer table of size: %d\n", Agent->routing->size);

	while (temp_peer != NULL) {
		display_peer_info(temp_peer);
		temp_peer = temp_peer->next_peer;
	}
	printf("-----------------------------------------------\n");
}

void
add_peer_entry(peer_t* new_peer)
{
	print_info("ROUTER - Added new peer to routing table");

	if (Agent->routing->size == 0) {
		Agent->routing->table = new_peer;
		Agent->routing->size++;
		return;
	}

	new_peer->next_peer = Agent->routing->table;
	Agent->routing->table = new_peer;
	Agent->routing->size++;
}

peer_t*
create_peer_entry(char* ip_addr, int port, char* agent_name)
{
	peer_t* new_peer = (peer_t*)malloc(sizeof(peer_t));

	new_peer->ip_addr = ip_addr;
	new_peer->port = port;
	new_peer->agent_name = agent_name;
	new_peer->next_peer = NULL;
	
	print_info("ROUTER - Created new peer");
	return new_peer;
}

peer_t*
remove_peer_entry(char* agent_name)
{
	peer_t* temp_peer = Agent->routing->table;
	peer_t* prev_peer = NULL;
	peer_t* removed_peer;
	
	while (temp_peer != NULL) {
		if (strncmp(temp_peer->agent_name, agent_name, strlen(agent_name)) == 0) {
			printf("[+] ROUTER - Peer entry removed for %s\n", agent_name);
			if (prev_peer == NULL) {
				removed_peer = Agent->routing->table;
				Agent->routing->table = Agent->routing->table->next_peer;
				Agent->routing->size--;
				return removed_peer;
			}
			removed_peer = temp_peer;
			prev_peer->next_peer = temp_peer->next_peer;
			Agent->routing->size--;
			return removed_peer;
		}
		prev_peer = temp_peer;
		temp_peer = temp_peer->next_peer;
	}
	
	printf("[!] ROUTER - Unable to remove peer %s\n", agent_name);
	return NULL;
}

peer_t*
find_peer_info(char* agent_name)
{
	if (Agent->routing->size == 0) return NULL;

	peer_t* temp_peer = Agent->routing->table;

	while (temp_peer != NULL) {
		if (strncmp(temp_peer->agent_name, agent_name, strlen(agent_name)) == 0) {
			printf("[+] ROUTER - Entry found for peer %s\n", agent_name);
			return temp_peer;
		}
		temp_peer = temp_peer->next_peer;
	}
	return NULL;
}

