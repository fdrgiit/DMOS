#include "sem.h"
#include <stddef.h>
#include <stdio.h>

//Semaphore_t *portMutex;		//For strategy 1

typedef struct Msg 
{
	int msg [10];
}Msg;
/*
typedef struct Port		//For strategy 1
{
	int portNum;
	int readPos, writePos;
	Msg msgs[10];
	Semaphore_t *portProdSem, *portConsSem;
}Port;
*/

typedef struct Port		//For strategy 2
{
	int portNum;
	int readPos, writePos;
	Msg msgs[10];
	Semaphore_t *portProdSem, *portConsSem, *portMutex;
}Port;

Port* CreatePort(int num)
{
	Port *newPort = (Port*) malloc(sizeof(Port));
	
	if(newPort != NULL)
	{
		newPort->portProdSem = CreateSem(10);
		newPort->portConsSem = CreateSem(0);
		newPort->portMutex = CreateSem(1);		//For Strategy 2
		newPort->portNum = num;
		newPort->readPos = 0;
		newPort->writePos = 0;
		return newPort;
	}
	
	return NULL;
}

void Send (Port **port, int *msg)
{
	int i = 0;
	
	P(&((*port)->portProdSem));
	//P(&portMutex);		//For strategy 1
	P(&((*port)->portMutex));		//For strategy 2
	
	//printf("sending on port %d \n", (*port)->portNum);
	
	for(; i < 10; i++)
	{
		(*port)->msgs[(*port)->writePos].msg[i] = msg[i];
	}
	
	(*port)->writePos = (((*port)->writePos) + 1) % 10;
	
	//V(&portMutex);		//For strategy 1
	V(&((*port)->portMutex));		//For strategy 2
	V(&((*port)->portConsSem));		
}

void Receive(Port **port, int *msg)
{
	int i = 0;
	
	P(&((*port)->portConsSem));
	//P(&portMutex);		//For strategy 1
	P(&((*port)->portMutex));		//For strategy 2
	
	//printf("receiving on port %d \n", (*port)->portNum);
	
	for(; i < 10; i++)
	{
		msg[i] = (*port)->msgs[(*port)->readPos].msg[i];
	}
	
	(*port)->readPos = (((*port)->readPos) + 1) % 10;
	
	/*
	for (i = 0; i < 10; i++)
	{
		printf("%d ", msg[i]);
	}
	
	printf("\n");
	*/
	//V(&portMutex);		//For strategy 1
	V(&((*port)->portMutex));		//For strategy 2
	V(&((*port)->portProdSem));
}

