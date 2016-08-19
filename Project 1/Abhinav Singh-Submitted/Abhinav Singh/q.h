#include "TCB.h"
 
TCB_t *initQ () 
{
	TCB_t *Q = NULL;
	return Q;
}
 
void AddQ(TCB_t *tcb,TCB_t **Q) 
{
	TCB_t *first,*last;
	if(*Q == NULL ) // If Queue is Empty 
	{
		tcb -> prev = tcb;
		tcb -> next = tcb;
		*Q = tcb;
		return;
	}
	else 
	{
		first = *Q; // 1st node from the head
		last = first -> prev; // last node as its prev of 1st
 
		//Circular Queue
		tcb -> next = first;
		tcb -> prev = last;
	 
		first -> prev = tcb;
		last -> next = tcb;
	}
}
 
TCB_t *DelQ(TCB_t **Q) 
{
	if(*Q == NULL) // If no elements are present in the Queue 
	{
		printf("Queue is Empty\n");
		return NULL;
	}
	
	TCB_t *curr,*last,*first;
	curr = *Q ;
	first = curr; 
	last = curr -> prev;
	curr = curr-> next; 
	last -> next = curr;
	curr -> prev = last; 
	first -> next = first -> prev = NULL; // remove all links of 1st to remove dangling pointer

	if(first == last)
	{*Q = NULL;} // removing last element so Q empty
	
	else
	{*Q = curr;} //Change starting point of the Q to 2nd value from 1st
	return first;
}
 
TCB_t *RotateQ(TCB_t **Q) 
{
	TCB_t *curr = *Q;
	curr = curr -> next;
	*Q = curr;
	return curr;
}
 
void printQ(TCB_t *Q) 
{
	printf("Queue Has Functions:\n");
	TCB_t *curr;
	int i = 1;
	curr = Q;

	if(curr == NULL) 
	{
		printf("Queue is Empty\n");
		return;
	}

	do
	{
		printf("%d ",curr -> i);
		curr = curr -> next;
	}while(curr != Q);

	printf("\n");
}
