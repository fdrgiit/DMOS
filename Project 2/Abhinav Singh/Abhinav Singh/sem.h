#include "threads.h"
#include <stddef.h>
#include <stdio.h>

struct Semaphore_t 
{
	int semaphoreCount, queueCount;
	struct TCB_t *SemQ;
};


struct Semaphore_t*  CreateSem(int InputValue) //mallocs a semaphore structure, initilizes it to the InitValue and returns the pointer to the semaphore
{
	struct Semaphore_t *newSem = (struct Semaphore_t*)malloc(sizeof(struct Semaphore_t));
	if(newSem != NULL)
	{
		newSem->semaphoreCount = InputValue;
		newSem->queueCount = 0;
		return newSem;
	}
	
	return NULL;
}


void P(struct Semaphore_t **sem) //takes a pointer to the semaphore and decrements it; if the value is less than zero then blocks the process in the queue associated with the semaphore.
{
	(*sem)->semaphoreCount--;

	if((*sem)->semaphoreCount < 0)
	{
		struct TCB_t *flag;
        	flag = DelQ(&(RunQ));
        	AddQ(&((*sem)->SemQ), flag);
        	(*sem)->queueCount++;
        	swapcontext(&(flag->context), &(RunQ->context));
	}
}


void V(struct Semaphore_t **sem) //increments the semaphore and if the value is 0 or negative, then takes a PCB out of the semaphore queue and puts it into the run queue. also yields to the next runnable process
{
	(*sem)->semaphoreCount++;

	if((*sem)->semaphoreCount <= 0)
	{
		struct TCB_t *flag;
		flag = DelQ(&((*sem)->SemQ));
		(*sem)->queueCount--;
        	AddQ(&(RunQ), flag);
	}
	
	yield();
}

