#include "q.h"

TCB_t *Q;
int count_threads = 0;

void start_thread(void (*function)(void))
{ 
	// begin pseudo code
	//allocate a stack (via malloc) of a certain size (choose 8192)
	void *stackP = malloc(8192);

	//allocate a TCB (via malloc)
	TCB_t *tcb = (TCB_t *) malloc(sizeof(TCB_t));

	//call init_TCB with appropriate arguments
	init_TCB (tcb,function, stackP, 8192);
	tcb -> i = ++count_threads;

	//call addQ to add this TCB into the RunQ which is a global header pointer
	AddQ(tcb,&Q);
	printQ(Q);
	printf("Thread %d Initialised\n",count_threads);
	//end pseudo code

}
 
void run()
{
	ucontext_t parent;     // get a place to store the main context, for faking
	getcontext(&parent);   // magic sauce
	swapcontext(&parent, &(Q->context));  // start the first thread
}
 
void yield() // similar to run
{
	printQ(Q);

	//rotate the run Q;
	TCB_t *curr = Q;
	TCB_t *RunQ = RotateQ(&Q);

	//swap the context, from previous thread to the thread pointed to by runQ
	printf("Switching from Thread %d to Thread %d\n",curr->i,RunQ->i);
	swapcontext(&(curr -> context), &(RunQ->context));

}
 
void exitFunction() 
{
	//rotate the run Q;
	TCB_t *curr = Q;
	DelQ(&Q);
	
	if(Q == NULL) return;

	printQ(Q);
	TCB_t *RunQ = Q;

	//swap the context, from previous thread to the thread pointed to by runQ
	printf("Exiting Thread %d to Thread %d\n",curr->i,RunQ->i);
	printQ(Q);
	swapcontext(&(curr -> context), &(RunQ->context));
}
