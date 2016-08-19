#include <ucontext.h>
#include <string.h>
//description of arguments
// 1. pointer to the function, to be executed
// 2. pointer to the thread stack
// 3. size of stack

struct TCB_t
{
	ucontext_t context;
	struct TCB_t *next, *prev;
} TCB_t;

struct TCB_t *RunQ;

void init_TCB (struct TCB_t *tcb, void *function, void *stackP, int stack_size)
{
	memset(tcb, '\0', sizeof(struct TCB_t));
	getcontext(&tcb->context);  //to get parent context
	tcb->context.uc_stack.ss_sp = stackP;  
	tcb->context.uc_stack.ss_size = (size_t) stack_size;
	makecontext(&tcb->context, function, 0); //context ready
}
