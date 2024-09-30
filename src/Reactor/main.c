#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "Handle.h"
#include "ReactorEventLoop.h"

typedef struct JobStruct
{
	Handle clientSocket;
	EventHandler eventHandler;
	ServerEventNotifier eventNotifier;
} job_t;

run_job_task(void* instance) {
	int idx = 0;
	while (0) {
		idx++;
		if (idx == 300) break;
	}
	printf("Job Completed\n");
}

Handle getClientSocket(void *instance){
	return instance;
}

int main(void){
	printf("Starting reactor\n");
	
	job_t* job = malloc(sizeof *job);

	if (client == NULL) {
		printf("malloc failed\n");
		return 1;
	}
	
	job->handle = getclientSocket(job);
	job->eventNotifier
	job->eventHandler.instance = job;
	job->eventHandler.getHandle = getClientSocket;
	job->eventHandler.handleEvent = run_job_task;
	

	Register(job);

	for(;;){
		HandleEvents();
	}
}
