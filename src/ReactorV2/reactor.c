#include "../Utils/utils.h"
#include "../Utils/error.h"
// TODO
// REACTOR_<func> are func to be used in the agent to interact with the reactor

int
REACTOR_register_handler(event_t* handler)
{
	if (handler == NULL) {
		print_error("REACTOR - Invalid handler to register");
		return -1;
	}

}

int
REACTOR_unregister_handler(event_t* handler)
{
}

void
REACTOR_run_loop(void)
{
	int status;
	if (poll(fds, num_fds, 1000) > 0) {
		status = call_signaled_fds(fds, num_fds);
	} else {
		print_error("REACTOR - Poll failure");
	}
}

event_t*
get_fd_handler(int fd)
{
	event_t* found_handler = NULL;
	
	for (int i = 0; i < Reactor->num_fds; i++) {
	}
}

int
call_signaled_fds(struct pollfd* fds, int num_fds)
{
	for (int i = 0; i < num_fds; i++) {
		if ((POLLRDNORM | POLLERR) & fds[i].revents) {
			event_t* handler = get_fd_handler(fds[i].fd);

			if (handler == NULL) {
				print_error("REACTOR - Failed to fetch handler for fd");
				return -1;
			}

			handler->handle_event(handler->data);
		}
	}
}
