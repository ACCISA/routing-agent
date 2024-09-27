#include "../Router/router.h"
#include "../Utils/utils.h"
#include "../Utils/error.h"
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
add_route_entry(peer_t* new_peer)
{
	new_peer->next_route = Agent->routing->table;
	Agent->routing->table = new_peer;
	print_info("ROUTER - Added new peer to routing table");
}

peer_t*
create_peer_entry(char* ip_addr, int port, char* agent_name)
{
	peer_t* new_peer = (peer_t*)malloc(sizeof(peer_t));

	new_peer->ip_addr = ip_addr;
	new_peer->port = port;
	new_peer->agent_name = agent_name;
	new_peer->next_route = NULL;
	
	print_info("ROUTER - Created new peer");
	return new_peer;
}

peer_t*
find_agent_info(char* agent_name)
{
	peer_t* temp_peer = Agent->routing->table;

	while (temp_peer != NULL) {
		if (strncmp(temp_peer->agent_name, agent_name, strlen(agent_name)) == 0) {
			printf("[+] ROUTER - Entry found for peer %s\n", agent_name);
			return temp_peer;
		}
		temp_peer = temp_peer->next_route;
	}
	return NULL;
}
