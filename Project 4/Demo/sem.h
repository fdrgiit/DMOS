#include "threads.h"
#include <stddef.h>
#include <stdio.h>

typedef struct Semaphore_t 
{
	int semCounter, qCount;
	struct TCB_t *SemQ;
}Semaphore_t;

//mallocs a semaphore structure, initilizes it to the InitValue and returns the pointer to the semaphore
//Semaphore_t* CreateSem(struct Semaphore_t *sem, int InputValue)
//Semaphore_t*  CreateSem(struct Semaphore_t *sem, int InputValue)
Semaphore_t*  CreateSem(int InputValue)
{
	Semaphore_t *newSem = (Semaphore_t*)malloc(sizeof(Semaphore_t));
	if(newSem != NULL)
	{
		newSem->semCounter = InputValue;
		newSem->qCount = 0;
		return newSem;
	}
	
	return NULL;
}

//takes a pointer to the semaphore and decrements it; if the value is less than zero then blocks the process in the queue associated with the semaphore.
void P(Semaphore_t **sem)
{
	(*sem)->semCounter--;
	if((*sem)->semCounter < 0)
	{
		struct TCB_t *temp;
        	temp = DelQ(&(RunQ));
        	AddQ(&((*sem)->SemQ), temp);
        	(*sem)->qCount++;
        	swapcontext(&(temp->context), &(RunQ->context));
	}
}

//increments the semaphore and if the value is 0 or negative, then takes a PCB out of the semaphore queue and puts it into the run queue. also yields to the next runnable process
void V(Semaphore_t **sem)
{
	(*sem)->semCounter++;
	if((*sem)->semCounter <= 0)
	{
		struct TCB_t *temp;
		temp = DelQ(&((*sem)->SemQ));
		(*sem)->qCount--;
        	AddQ(&(RunQ), temp);
	}
	
	yield();
}

