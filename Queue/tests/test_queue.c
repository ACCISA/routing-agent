#include <stdarg.h>

#include "../queue.h"
#include "../../Utils/utils.h"

void test1_task(int n, ...)
{
	va_list ptr; 
	int arg1, arg2;

	va_start(ptr, n);
		arg1 = va_arg(ptr, int);
		arg2 = va_arg(ptr, int);
	va_end(ptr);

	print_info("Completed task1:");
	printf("result: %d\n", arg1+arg2);
}



void test1_cb(int n, ...)
{	
	print_info("test1 callback ran");
}



void test2_task(int n, ...)
{
	va_list ptr; 
	int arg1, arg2;

	va_start(ptr, n);
		arg1 = va_arg(ptr, int);
		arg2 = va_arg(ptr, int);
	va_end(ptr);

	print_info("Completed task2:");
	printf("result: %d\n", arg1+arg2);
}



void test2_cb(int n, ...)
{	
	print_info("test2 callback ran");
}

void test3_task(int n, ...)
{
	va_list ptr; 
	int arg1, arg2;

	va_start(ptr, n);
		arg1 = va_arg(ptr, int);
		arg2 = va_arg(ptr, int);
	va_end(ptr);

	print_info("Completed task3:");
	printf("result: %d\n", arg1+arg2);
}



void test3_cb(int n, ...)
{	
	print_info("test3 callback ran");
}

void process_job(job_t* job)
{
	job->task_func(2, 1, 2);
	job->task_cb(1, 2);
}

int main(void) {
	job_t* task1 = create_job("test1", test1_task, test1_cb);
	job_t* task2 = create_job("test2", test2_task, test2_cb);
	job_t* task3 = create_job("test3", test3_task, test3_cb);

	rqueue_t* reactor_queue = (rqueue_t*)malloc(sizeof(rqueue_t));
	
	// task2 should run first as it was set to high priority
	add_job(reactor_queue, task1, 0);
	add_job(reactor_queue, task2, 1);
	add_job(reactor_queue, task3, 0);

	display_reactor_queue(reactor_queue);

	process_job(get_job(reactor_queue));
	process_job(get_job(reactor_queue));
	process_job(get_job(reactor_queue));

	return 0;
}
