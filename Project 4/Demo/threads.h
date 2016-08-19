#include "q.h"
#include <stdlib.h>
#include <ucontext.h>

void start_thread(void (*function) (void))
{
	/*
	allocate a stack (via malloc) of a certain size (choose 8192)
	allocate a TCB (via malloc)
	call init_TCB with appropriate arguments
	call AddQ to add this TCB to the "RunQ" which is a global header pointer
	*/
	
	void *stack = malloc(8192);
	struct TCB_t *tcb = (struct TCB_t*)malloc(sizeof(struct TCB_t));
	init_TCB(tcb, function, stack, 8192);
	// init_TCB(tcb, function, stack, sizeof(stack)); //would this work
	AddQ(&RunQ, tcb);
}
void run()
{
	//real code
	ucontext_t parent;	//get a context to store the main context, for faking
	getcontext(&parent); 	//magic sauce
	swapcontext(&parent, &(RunQ->context));	//start the first thread
}

void yield () //similar to rum
{
	//rotate the RunQ
	//swap the context, from previous thread to the thread pointed to by RunQ
	struct TCB_t *currentThread;
	currentThread = RunQ;
	RotateQ(&RunQ);
	swapcontext(&(currentThread->context), &(RunQ->context));
}
