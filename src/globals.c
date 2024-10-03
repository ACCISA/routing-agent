#include "globals.h"
#include "Utils/utils.h"
#include "Utils/error.h"

AgentInfo* Agent = NULL;

void
initialize_agent_info(void)
{
	print_info("GLOBAL - Agent global variable initialized");
	Agent = (AgentInfo*)malloc(sizeof(AgentInfo));
	Agent->agent_name = (char*)malloc(sizeof(char)*100);
	Agent->ip_addr = (char*)malloc(sizeof(char)*50);
	Agent->routing = (routing_t*)malloc(sizeof(routing_t));
	Agent->routing->size = 0;
	Agent->routing->table = NULL;
	Agent->msg_store = (msg_store_t*)malloc(sizeof(msg_store_t*));
	Agent->msg_store->size = 0;
	Agent->msg_store->msg = NULL;
	Agent->reactor_queue = (rqueue_t*)malloc(sizeof(rqueue_t));
}

int
is_agent_init(void)
{
	if (Agent == NULL || Agent->routing == NULL || Agent->msg_store == NULL) {
		print_info("GLOBAL - Agent was not intialized first");
		return 0;
	}
	return 1;
}

void
set_agent_name(char* name)
{
	if (is_agent_init() == 0) return;
	print_info("GLOBAL - Set global variable agent_name");
	strncpy(Agent->agent_name, name, strlen(name));
	Agent->agent_name[strlen(name)] = '\0';
}

void
set_agent_ip_addr(char* ip_addr)
{
	if (is_agent_init() == 0) return;
	print_info("GLOBAL - Set global variable ip_addr");
	strncpy(Agent->ip_addr, ip_addr, strlen(ip_addr));
	Agent->ip_addr[strlen(ip_addr)] = '\0';
}

void
set_agent_peer_table(routing_t* peer_table)
{	
	if (is_agent_init() == 0) return;
	Agent->routing = peer_table;
	print_info("GLOBAL - Set global variable routing");
}

void
set_agent_port(int port)
{ 
	if (is_agent_init() == 0) return;
	print_info("GLOBAL - Set global variable port");
	Agent->port = port;
}

void
set_agent_key(unsigned char* decrypt_key)
{
	if (is_agent_init() == 0) return;
	print_info("GLOBAL - Set global variable decrypt_key");
	Agent->decrypt_key = decrypt_key;
}

void
set_agent_iv(unsigned char* iv)
{
	if (is_agent_init() == 0) return;
	print_info("GLOBAL - Set global variable iv");
	Agent->iv = iv;
}

void
display_agent_info(void)
{
	if (is_agent_init() == 0) return;
	if (Agent == NULL || Agent->agent_name == NULL || Agent->ip_addr == NULL) {
		print_error("GLOBAL - Agent global variable is not initialized");
		return;
	}
	print_info("GLOBAL - Displaying agent info");
	printf("[+] agent_name: %s\n", Agent->agent_name);
	printf("[+] ip_addr: %s\n", Agent->ip_addr);
	printf("[+] port: %d\n", Agent->port);

}
