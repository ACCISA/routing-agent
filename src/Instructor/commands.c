#include "../Instructor/task.h"
#include "../Instructor/commands.h"
#include "../Reactor/reactor.h"
#include "../Queue/queue.h"
#include "../Router/router.h"
#include "../Utils/utils.h"
#include "../Utils/error.h"
#include "../globals.h"

#include <limits.h>

int
get_hostname_command(void* data)
{
	task_t* task = (task_t*)data;
	
	char hostname[HOST_NAME_MAX+1];

	print_info("TASK - Running hostname task");
	if (gethostname(hostname, sizeof(hostname)) != 0) {
		task->result = "n/a";
		return -1;
	}
	task->result = hostname;
	return 0;
}

int
get_hostname_command_cb(void* data)
{
	print_info("INSTRUCTOR - Running get_hostname_command_cb");
	REACTOR_add_job((void (*) (void *)) send_routing_data, (void (*) (void *)) send_routing_data_cb, (task_t*)data);
	return 0;
}

int
print_agent_info_command(void* data)
{
	task_t* task = (task_t*)data;
	task->result = "completed";
	display_agent_info();
	return 0;
}

int
print_agent_info_command_cb(void* data)
{
	print_info("INSTRUCTOR - Running print_agent_info_command_cb");
	REACTOR_add_job((void (*) (void *)) send_routing_data, (void (*) (void *)) send_routing_data_cb, (task_t*)data);
	return 0;
}
