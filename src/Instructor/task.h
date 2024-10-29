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

int get_instruction_func(int instruction);
int get_instruction_cb(int instruction);
int initialize_instructions(void);

void get_hostname_instruction(void* data);

#endif
