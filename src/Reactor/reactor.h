#ifndef REACTOR_H
#define REACTOR_H

#include "../globals.h"


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
