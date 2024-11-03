#include "Utils/utils.h"
#include "Utils/error.h"
#include "Queue/queue.h"
#include "Config/config.h"
#include "Server/server.h"
#include "Reactor/reactor.h"
#include "Router/router.h"
#include "Message/message.h"
#include "Instructor/task.h"
#include "Instructor/commands.h"
#include "globals.h"


AgentInfo* Agent = NULL;

void
initialize_agent_info(void)
{
	print_info("GLOBAL - Agent global variable initialized");
	Agent 					= (AgentInfo*)malloc(sizeof(AgentInfo));
	Agent->agent_name 			= (char*)malloc(sizeof(char)*100);
	Agent->ip_addr 				= (char*)malloc(sizeof(char)*50);
	Agent->routing 				= (routing_t*)malloc(sizeof(routing_t));
	Agent->routing->size 			= 0;
	Agent->routing->table 			= NULL;
	Agent->msg_store 			= (msg_store_t*)malloc(sizeof(msg_store_t*));
	Agent->msg_store->size 			= 0;
	Agent->msg_store->msg 			= NULL;
	Agent->reactor_queue 			= (rqueue_t*)malloc(sizeof(rqueue_t));
	Agent->reactor_queue->size 		= 0;
	Agent->reactor_queue->job_head 		= NULL;
	Agent->handler_list 			= (rhandler_list_t*)malloc(sizeof(rhandler_list_t));
	Agent->handler_list->size 		= 0;
	Agent->handler_list->handler	 	= NULL;
	Agent->decrypt_key			= (unsigned char*)malloc(sizeof(unsigned char)*32);
	Agent->iv				= (unsigned char*)malloc(sizeof(unsigned char)*16);
	Agent->commands_list			= (commands_list_t*)malloc(sizeof(commands_list_t));
	Agent->commands_list->size		= 0;
	Agent->commands_list->command		= NULL;
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
	strncpy(Agent->decrypt_key, decrypt_key, 32);
}

void
set_agent_iv(unsigned char* iv)
{
	if (is_agent_init() == 0) return;
	print_info("GLOBAL - Set global variable iv");
	strncpy(Agent->iv, iv, 16);
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
	printf("[+] peer_table_size: %d\n", Agent->routing->size);
	printf("[+] message_store_size: %d\n", Agent->msg_store->size);
	printf("[+] reactor_queue_size: %d\n", Agent->reactor_queue->size);
	printf("[+] handler_list_size: %d\n", Agent->handler_list->size);
	printf("[+] commands_list_size: %d\n", Agent->commands_list->size);

}
