#include "q.h"
#include <stdlib.h>
#include <ucontext.h>
#include <stdio.h>

//TCB_t *Q;
//int count_threads = 0;

void start_thread(void (*function)(void))
{
	// begin pseudo code
	//allocate a stack (via malloc) of a certain size (choose 8192)
	void *stackP = malloc(8192);

	//allocate a TCB (via malloc)
	struct TCB_t *tcb = (struct TCB_t*)malloc(sizeof(struct TCB_t));

	//call init_TCB with appropriate arguments
	init_TCB (tcb, function, stackP, 8192);
	//tcb -> i = ++count_threads;

	//call addQ to add this TCB into the RunQ which is a global header pointer
	AddQ(&RunQ, tcb);
	//printQ(Q);
	//printf("Thread %d Initialised\n",count_threads);
	//end pseudo code


}
 
void run()
{
	ucontext_t parent;     // get a place to store the main context, for faking
	getcontext(&parent);   // magic sauce
	swapcontext(&parent, &(RunQ->context));  // start the first thread
}
 
void yield() // similar to run
{
	//printQ(Q);

	//rotate the run Q;
	struct TCB_t *curr;
	curr = RunQ;
	RotateQ(&RunQ);

	//swap the context, from previous thread to the thread pointed to by runQ
	//printf("Switching from Thread %d to Thread %d\n",curr->i,RunQ->i);
	swapcontext(&(curr->context), &(RunQ->context));
}
