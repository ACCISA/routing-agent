#include "../Instructor/task.h"

#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int
initialize_instructor(void)
{

}

int
get_instruction_func(int instruction)
{

}

void
get_hostname_instruction(void* data){
	task_t* task = (task_t*)data;
	

	char* hostname = (char*)malloc(sizeof(char)*40);
	print_info("TASK - Running hostname task");

	if (gethostname(hostname, sizeof(hostname)) == 0) {
		task->result = hostname;
	}
}
