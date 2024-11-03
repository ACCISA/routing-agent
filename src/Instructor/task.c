#include "../Instructor/task.h"
#include "../Instructor/commands.h"
#include "../Utils/utils.h"
#include "../Queue/queue.h"
#include "../Reactor/reactor.h"
#include "../globals.h"

#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int
initialize_commands(void)
{
	command_t* hostname_command = create_command(0, get_hostname_command, get_hostname_command_cb);
	add_command(hostname_command);

	command_t* print_agent_command = create_command(1, print_agent_info_command, print_agent_info_command_cb);
	add_command(print_agent_command);
}

func_ptr_type*
get_instruction(int instruction)
{
	static func_ptr_type instruction_funcs[2];
	command_t* command = Agent->commands_list->command;

	while (command != NULL) {
		if (command->command_num == instruction) {
			instruction_funcs[0] = command->command_func;
			instruction_funcs[1] = command->command_cb;
			print_info("INSTRUCTOR - Retrieved command functions");
			return instruction_funcs;
		}
		command = command->next_command;
	}
	return NULL;
}

command_t*
create_command(int command_num, int (*command_func)(void* data), int (*command_cb)(void* data))
{
	command_t* command = (command_t*)malloc(sizeof(command_t));

	command->command_num = command_num;
	command->command_func = command_func;
	command->command_cb = command_cb;
	command->next_command = NULL;

	return command;
}

int
add_command(command_t* command)
{
	if (Agent->commands_list->size == 0) {
		Agent->commands_list->command = command;
		Agent->commands_list->size++;
		print_info("INSTRUCTOR - Registered new command");
		return;
	}

	command_t* temp_command = Agent->commands_list->command;

	while (temp_command != NULL) {
		if (temp_command->next_command != NULL && temp_command->command_num == command->command_num) {
			print_error("INSTRUCTOR - Duplicate instruction num found");
			return -1;
		}
		if (temp_command->next_command == NULL) {
			temp_command->next_command = command;
			Agent->commands_list->size++;
			print_info("INSTRUCTOR - Registered new command");
			return 0;
		}
		temp_command = temp_command->next_command;
	}
}
