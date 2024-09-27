#include "globals.h"
#include "Utils/utils.h"

void
initialize_agent_info()
{
	print_info("GLOBAL - Initialize Agent global variable initialized");
	Agent->agent_name = (char*)malloc(sizeof(char)*100);
	Agent->ip_addr = (char*)malloc(sizeof(char)*50);
	Agent->routing = (routing_t*)malloc(sizeof(routing_t));
	Agent->routing->size = 0;
	Agent->routing->table = (route_t*)malloc(sizeof(route_t));
}

void
set_agent_name(char* name)
{
	print_info("GLOBAL - Set global variable agent_name");
	strncpy(Agent.agent_name, name, strlen(name));
	Agent.agent_name[strlen(name)] = '\0';
}

void
set_agent_ip_addr(char* ip_addr)
{
	print_info("GLOBAL - Set global variable ip_addr");
	strncpy(Agent.ip_addr, ip_addr, strlen(ip_addr));
	Agent.ip_addr[strlen(ip_addr)] = '\0';
}

void
set_agent_port(int port)
{ 
	print_info("GLOBAL - Set global variable port");
	Agent.port = port;
}

void
display_agent_info(void)
{
	if (Agent == NULL || Agent->agent_name == NULL || Agent->ip_addr == NULL) {
		print_error("GLOBAL - Agent global variable is not initialized");
		return;
	}
	print_info("GLOBAL - Displaying agent info");
	printf("[+] agent_name: %s\n", Agent->agent_name);
	printf("[+] ip_addr: %s\n", Agent->ip_addr);
	printf("[+] port: %d\n", Agent->port);

}
