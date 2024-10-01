#ifndef QUEUE_H
#define QUEUE_H


#include <stdio.h>
#include <stdlib.h>

typedef struct job {
	char* task_name;
	void (*task_func)(int n, ...);
	void (*task_cb)(int n, ...);
	struct job* next_job;
} job_t;

typedef struct job_queue {
	int	size;
	job_t* 	job_head;
} rqueue_t;

job_t* create_job(char* task_name,
		void (*task_func)(int n, ...),
		void (*task_cb)(int n, ...));
void add_job(rqueue_t* reactor_queue, job_t* new_job, int priority);
void display_reactor_queue(rqueue_t* reactor_queue);
job_t* get_job(rqueue_t* reactor_queue);

#endif
