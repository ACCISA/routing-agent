#include "Config/config.h"
#include "Server/server.h"
#include "Reactor/reactor.h"
#include "Router/router.h"
#include "Message/message.h"
#include "Queue/queue.h"
#include "globals.h"

#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
	
	if (argc != 2) {
		return 1;
	}
	
	init_openssl();
	
	set_agent_from_config(argv[1]);

	display_agent_info();

	int sockfd = create_server_socket();

	rhandler_t* server_handler = (rhandler_t*)malloc(sizeof(rhandler_t));

	struct pollfd fd;
	fd.fd = sockfd;
	fd.events = POLLIN | POLLOUT | POLLERR;

	server_handler->event_handler 		= read_routing_data;
	server_handler->event_handler_cb 	= read_routing_data_cb;
	server_handler->fd			= fd;
	server_handler->data 			= NULL;
	server_handler->next_handler 		= NULL;

	REACTOR_register_handler(server_handler);

	REACTOR_run_loop();

}
