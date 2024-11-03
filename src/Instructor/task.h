#ifndef TASK_H_
#define TASK_H_

#include "../Message/message.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct task {
	connection_t* connection;
	rmessage_t* routing_message;
	char* result;
} task_t;

typedef struct command {
	int command_num;
	int (*command_func)(void* data);
	int (*command_cb)(void* data);
	struct commands* next_command;
} command_t;

typedef struct commands_list {
	int size;
	command_t* command;
} commands_list_t;

typedef int (*func_ptr_type)(void*);

func_ptr_type* get_instruction(int instruction);
command_t* create_command(int command_num, int (*command_func)(void* data),
		int (*command_cb)(void* data));
int get_instruction_cb(int instruction);
int initialize_commands(void);


#endif
