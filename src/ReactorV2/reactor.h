#ifndef REACTOR_H
#define REACTOR_H

#include "../globals.h"


int REACTOR_register_handler(rhandler_t* handler);
int REACTOR_run_loop(void);
int REACTOR_unregister_handler(rhandler_t* handler);

int remove_registered_handler(rhandler_t* handler);
int add_registered_handler(rhandler_t* handler);
void call_signaled_handlers(void);

#endif
