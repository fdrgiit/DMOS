#include "sem.h"
#include <stddef.h>
#include <stdio.h>

struct Message 
{
	int mesg [10];
}Message;


struct Ports		
{
	int portCount;
	int readCount, writeCount;
	struct Message msgs[10];
	//int storemsg[10];
	struct Semaphore_t *producer, *consumer, *mutex;
}Ports;

struct Ports* Initialize(int num)
{
	struct Ports *newPort = (struct Ports*) malloc(sizeof(struct Ports));
	
	if(newPort != NULL)
	{
		newPort->producer = CreateSem(10);
		newPort->consumer = CreateSem(0);
		newPort->mutex = CreateSem(1);		
		newPort->portCount = num;
		newPort->readCount = 0;
		newPort->writeCount = 0;
		return newPort;
	}
	
	return NULL;
}

void Send (struct Ports **port, int *mesg) 
{
	int i = 0;
	P(&((*port)->producer));

	P(&((*port)->mutex));		
	
	for(; i < 10; i++)
	{
		(*port)->msgs[(*port)->writeCount].mesg[i] = mesg[i];
	}
	
	(*port)->writeCount = (((*port)->writeCount) + 1) % 10;
	
	
	V(&((*port)->mutex));
	V(&((*port)->consumer));
}

void Receive(struct Ports **port, int *mesg)
{
	int i = 0;
	
	P(&((*port)->consumer));
	
	P(&((*port)->mutex));	
	
	for(; i < 10; i++)
	{
		mesg[i] = (*port)->msgs[(*port)->readCount].mesg[i];
	}
	
	(*port)->readCount = (((*port)->readCount) + 1) % 10;
	
	
	V(&((*port)->mutex));		
	V(&((*port)->producer));
}

