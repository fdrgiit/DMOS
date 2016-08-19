#include "TCB.h"
#include <stddef.h>
#include <stdio.h>

void InitQ(struct TCB_t **Q) // initializing queue to null
{
	(*Q) = NULL;
}

void AddQ (struct TCB_t **Q, struct TCB_t *item) // adding new item to the end of the queue
{
	if((*Q)) //if there are one or more items
	{
		item->next = (*Q);
		item->prev = (*Q)->prev;
		(*Q)->prev->next = item;
		(*Q)->prev = item;
	}else //if it was an empty queue
	{
		(*Q) = item;
		(*Q)->prev = (*Q);
		(*Q)->next = (*Q);
	}
}

struct TCB_t* DelQ(struct TCB_t **Q) // deleting the current head and returning the pointer to it
{
	struct TCB_t *temp;
	if(*Q) // if the queue exists
	{
		temp = (*Q);
		if ((*Q)->next == (*Q)) // if there is only one item in the queue
		{
			(*Q) = NULL;
		}else // if there are more than one item
		{
			(*Q)->prev->next = (*Q)->next;
			(*Q)->next->prev = (*Q)->prev;
			(*Q) = (*Q)->next;
		}
	}else // if queue is empty
	{
		temp = NULL;
		printf("Queue is empty");
	}
	return temp;
}

void RotateQ(struct TCB_t **Q) //shifting the head pointer to the next node so that the currently executing node becomes the last node in the queue
{
	(*Q) = (*Q)->next;
}
