#ifndef REACTOR_H
#define REACTOR_H

typedef struct EventHandler {
	void* data;
	int (*get_fd)(void* data);
	void (*handle_event)(void* data);
	struct EventHandler* next_hander;
} ehandler_t;

typedef struct EventHandlerRegistry {
	int size;
	event_t* event; 
} eregistry_t;

int REACTOR_register_handler();
int REACTOR_run_loop();
int REACTOR_unregister_handler();

int add_handler(ehandler_t* event_handler);


#endif
