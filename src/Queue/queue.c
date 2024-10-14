#include "../Queue/queue.h"
#include "../Utils/utils.h"
#include "../Utils/error.h"
#include "../globals.h"

job_t*
create_job(char* task_name, void (*task_func)(void* func_arg),
		void (*task_cb)(void* cb_arg),
		void* func_arg)
{
	job_t* new_job = (job_t*)malloc(sizeof(job_t));

	new_job->task_name = task_name;
	new_job->task_func = task_func;
	new_job->task_cb = task_cb;
	new_job->func_arg = func_arg;
	new_job->next_job = NULL;
	
	print_info("Created job");
	return new_job;
}

void
add_job(rqueue_t* reactor_queue, job_t* new_job, int priority)
{
	if (reactor_queue->job_head == NULL) {
		reactor_queue->job_head = new_job;
		print_info("Added job to empty queue");
		return;
	}


	if (priority == 1) {
		new_job->next_job = reactor_queue->job_head;
		reactor_queue->job_head = new_job;
		reactor_queue->size += 1;
		print_info("Added high priority job to queue");
		return;
	}

	job_t* temp_job = reactor_queue->job_head;

	while (temp_job != NULL) {
		if (temp_job->next_job == NULL) {
			temp_job->next_job = new_job;
			print_info("Added low priority job to queue");
			return;
		}
		temp_job = temp_job->next_job;
	}
}

void
display_reactor_queue(rqueue_t* reactor_queue)
{
	if (reactor_queue->job_head == NULL) {
		print_error("Reactor emtpy, unable to display");
		return;
	}

	print_info("Displaying reactor queue:");

	job_t* temp_job = reactor_queue->job_head;
	
	while (temp_job != NULL) {
		printf("task_name: %s\n", temp_job->task_name);
		temp_job = temp_job->next_job;
	}
}

job_t*
get_job(rqueue_t* reactor_queue)
{

	if (reactor_queue->job_head == NULL) {
		print_error("Empty reactor queue");
		return NULL;
	}

	job_t* temp_job = reactor_queue->job_head;
	reactor_queue->job_head = reactor_queue->job_head->next_job;

	reactor_queue->size -= 1;
	print_info("Popped job from reactor queue");
			
	return temp_job;
}
