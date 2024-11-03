#include "Config/config.h"
#include "Server/server.h"
#include "Reactor/reactor.h"
#include "Router/router.h"
#include "Message/message.h"
#include "Instructor/commands.h"
#include "Instructor/task.h"
#include "Queue/queue.h"
#include "globals.h"

#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

void background_task(void* arg)
{
	int* num = (int*)arg;
	*num = *num + 1;
	printf("BG - count: %d\n", *num); 
}

void background_task_cb(void *arg)
{
	// re-add the task back to the reactor queue
	REACTOR_add_job(background_task, background_task_cb, arg);
}

int main(int argc, char* argv[]) {
	
	if (argc != 2) {
		return 1;
	}

	server_t* server;
	
	init_openssl();

	initialize_agent_info();
	initialize_commands();

	set_agent_from_config(argv[1]);

	display_agent_info();
	
	int* num = (int*)malloc(sizeof(int));
	*num = 0;

	//REACTOR_add_job(background_task, background_task_cb, num);

	if ((server = create_server_struct()) == NULL) {
		print_error("MAIN - Unable to create server struct");
		return 1;	
	}

	rhandler_t* server_handler = (rhandler_t*)malloc(sizeof(rhandler_t));

	struct pollfd fd;
	fd.fd = server->sockfd;
	fd.events = POLLRDNORM;

	server_handler->event_handler 		= accept_client_connection;
	server_handler->event_handler_cb 	= accept_client_connection_cb;
	server_handler->fd			= fd;
	server_handler->data 			= (void*)server;
	server_handler->next_handler 		= NULL;


	REACTOR_register_handler(server_handler);
	while(1) {
		REACTOR_run_job();
		REACTOR_run_loop();
	}

}
