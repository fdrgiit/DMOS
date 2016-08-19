#include "TCB.h"
#include <stddef.h>
#include <stdio.h>
 
void InitQ(struct TCB_t **Q) // initializing queue to null. Before used syntax didn't work. DOn't know why.
{
	(*Q) = NULL;
}
 
void AddQ(struct TCB_t **Q, struct TCB_t *tcb) 
{
	struct TCB_t *first,*last;
	if(*Q == NULL ) // If Queue is Empty
	{
		(*Q) = tcb;		
		tcb -> prev = tcb;
		tcb -> next = tcb;
		return;
	}
	else 
	{
		first = (*Q); // 1st node from the head
		last = first->prev; // last node as its prev of 1st
 
		//Circular Queue
		tcb->next = first;
		tcb->prev = last;
	 	
		last->next = tcb;
		first->prev = tcb;
		
	}
}
 
struct TCB_t *DelQ(struct TCB_t **Q) 
{
	if(*Q == NULL) // If no elements are present in the Queue
	{
		printf("Queue is Empty\n");
		return NULL;
	}
	
	struct TCB_t *curr,*last,*first;
	curr = (*Q) ;
	first = curr; 
	last = curr->prev;
	curr = curr->next; 
	last->next = curr;
	curr->prev = last; 
	first->next = first->prev = NULL; // remove all links of 1st to remove dangling pointer

	if(first == last)
	{*Q = NULL;} // removing last element so Q empty
	
	else
	{*Q = curr;} //Change starting point of the Q to 2nd value from 1st
	return first;
}
 
void RotateQ(struct TCB_t **Q) //Pointer didn't work again.!!
{
	struct TCB_t *curr = (*Q);
	curr = curr->next;
	(*Q) = curr;
	//return curr;
}

