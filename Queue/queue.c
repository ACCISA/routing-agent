#include "../Queue/queue.h"
#include "../Utils/utils.h"
#include "../Utils/error.h"

job_t*
create_job(char* task_name, void (*task_func)(int n, ...), void (*task_cb)(int n, ...))
{
	job_t* new_job = (job_t*)malloc(sizeof(job_t));

	new_job->task_name = task_name;
	new_job->task_func = task_func;
	new_job->task_cb = task_cb;
	new_job->next_job = NULL;

	return new_job;
}

void
add_job(rqueue_t* reactor_queue, job_t* new_job, int priority)
{
	job_t* job_head = reactor_queue->job_head;

	if (priority == 1) {
		new_job->next_job = job_head;
		job_head = new_job;
		reactor_queue->size += 1;
		print_info("Added high priority job to queue");
		return;
	}

	job_t* temp_job = job_head;

	while (temp_job != NULL) {
		if (temp_job->next_job == NULL) {
			temp_job->next_job = new_job;
			print_info("Added low priority job to queue");
			return;
		}
		temp_job = temp_job->next_job;
	}
}

job_t*
get_job(rqueue_t* reactor_queue)
{
	job_t* job_head = reactor_queue->job_head;

	if (job_head == NULL) {
		print_error("Empty reactor queue");
	}

	job_t* temp_job = job_head;
	job_head = job_head->next_job;

	reactor_queue->size -= 1;
	print_info("Popped job from reactor queue");
			
	return temp_job;
}
