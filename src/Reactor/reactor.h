#ifndef REACTOR_H
#define REACTOR_H

#include <poll.h>

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
int REACTOR_register_handler(rhandler_t* handler);
int REACTOR_run_loop(void);
int REACTOR_unregister_handler(rhandler_t* handler);

int remove_registered_handler(rhandler_t* handler);
int add_registered_handler(rhandler_t* handler);
void call_signaled_handlers(void);
struct pollfd* get_fd(void);

#endif
