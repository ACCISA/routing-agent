#ifndef REACTOR_H_
#define REACTOR_H_

#include "../Queue/queue.h"

#include <poll.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

typedef struct handler {
	struct pollfd fd;
	void* data;
	int (*event_handler)(void* data);
	int (*event_handler_cb)(void* data);
	struct handler* next_handler;
} rhandler_t;

typedef struct handler_list {
	int  size;
	rhandler_t* handler;
} rhandler_list_t;


void REACTOR_add_job(void (*task_func)(void* func_arg), 
		void (*task_cb)(void* cb_arg),
		void* func_arg);
void REACTOR_run_job(void);
job_t* REACTOR_get_job(void);
int REACTOR_register_handler(rhandler_t* handler);
int REACTOR_run_loop(void);
int REACTOR_unregister_handler(int fd);

int remove_registered_handler(int fd);
int add_registered_handler(rhandler_t* handler);
rhandler_t* get_fd_handler(int fd);
void call_signaled_handlers(struct pollfd* fds);

#endif
