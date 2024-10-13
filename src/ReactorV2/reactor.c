#include "../ReactorV2/reactor.h"
#include "../Utils/utils.h"
#include "../Utils/error.h"
// TODO
// REACTOR_<func> are func to be used in the agent to interact with the reactor

int
REACTOR_register_handler(rhandler_t* handler)
{
	if (handler == NULL) {
		print_error("REACTOR - Invalid handler to register");
		return -1;
	}
	
	if (add_handler_registration(handler) < 0) {
		print_error("REACTOR - Failed to register new event handler");
		return -1;
	}

	print_info("REACTOR - Registered new event handler");
	return 0;
}

int
REACTOR_unregister_handler(rhandler_t* handler)
{
	if (remove_handler_registration(fd) < 0) {
		printf("[!] ROUTER - Unable to remove registerd handler (fd=%d)\n", fd);
	}
	printf("[+] ROUTER - Removed registered handle (fd=%d)\n", fd);
}

void
REACTOR_run_loop(void)
{
	int status;
	struct pollfd* fds = get_fds();

	if (poll(fds, num_fds, 1000) > 0) {
		 
		status = call_signaled_fds(fds, num_fds);
	} else {
		print_error("REACTOR - Poll failure");
	}
}

// TODO rewrite this
int
remove_registered_handler(rhandler_t* handler)
{
	if (Agent->handler_list->size == 0) return 0;

	rhandler_t* temp_handler = Agent->handler_list->handler;
	rhandler_t* prev_handler = NULL;


	while (temp_handler != NULL) {
		if (temp_handler->fd->fd  == handler->fd->fd) {
			if (prev_handler == NULL) {
				Agent->handler_list->handler = Agent->handler_list->handler->next_handler;
				Agent->handler_list->size--;
				return 0;
			}
			prev_handler->next_handler = temp_handler->next_handler;
			Agent->handler_list->size--;
			return 0;
		}
		prev_handler = temp_handler;
		temp_handler = temp_handler->next_handler;
	}
	return -1;
}

int
add_registered_handle(rhandler_t* handler)
{
	if (Agent->handler_list->size == 0) {
		Agent->handler_list->handler = handler;
		Agent->handler_list->size += 1;
		return 0;
	}

	ehandler_t* temp_handler = Agent->handler_list->handler;

	while (temp_handler != NULL) {
		if (temp_handler->next_handler == NULL) {
			temp_handler->next_handler = handler;
			Agent->handler_list->size += 1;
			return 0;
		}
		temp_handler = temp_handler->next_handler;
	}
}

void
call_signaled_handlers(void)
{
	rhandler_t* temp_handler = Agent->handler_list->handler;

	while (temp_handler != NULL) {
		if ((POLLRDNORM | POLLERR) & temp_handler->fd->revents) {
			// do we want to just run the job now?
			RECTOR_add_job(temp_handler->event_handler, 
					temp_handler->event_handler_cb,
					temp_handler->data);
		}
		temp_handler = temp_handler->next_handler;
	}
}
