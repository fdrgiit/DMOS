/*
NAME: ABHINAV SINGH
ASU ID: 1206277744
*/


#include "sem.h"
#include <stdio.h>
#include <unistd.h>

struct Semaphore_t *r_sem, *w_sem, *mutex;
int rwc = 0, wwc = 0, rc = 0, wc = 0, global_ID=0;

void reader_entry(int ID)
{
	printf("[reader: #%d]\ttrying to read\n", ID);
	P(&mutex); //Gets CS
	if (wwc > 0 || wc > 0) 
	{
	    printf("[reader: #%d]\tblocking for writer\n", ID);
	    rwc++;		
	    V(&mutex);		
	    P(&r_sem);		// Reader sleeps
	    rwc--;		// Decrements wait counter   
	}
	rc++;			//increments rc and enter
	if (rwc > 0)
	    V(&r_sem);		//passes the mutex to 1 Reader
	else
	{
	    V(&mutex);		// Final reader unlocks mutex
	}
}

void reader_exit(int ID)
{
	P(&mutex);		//Lock Mutex
	rc--;			// Reader Exit, Decrement counter
	if (rc == 0 && wwc > 0) 
	{
	    // Allow 1 writer
	    V(&w_sem);
	} else
	{
	    V(&mutex);
	}
}

void writer_entry(int ID)
{
	printf("\t\t\t\t[writer: #%d]\ttrying to write\n", ID);
	P(&mutex);		//Lock Mutex
	if (rc > 0 || wc > 0)	//Not ok to enter 
	{
	    printf("\t\t\t\t[writer: #%d] blocking for others\n", ID);
	    wwc++;		// increment wait count
	    V(&mutex);		// unlock mutex
	    // blocked
	    P(&w_sem);		// Writer Sleep  	    	
	    wwc--;		// When wake up, Mutex is passed.
	}
	wc++;			// increment writer count
	V(&mutex);		// unlock mutex
}

void writer_exit(int ID)
{
	P(&mutex);		// Lock Mutex
	wc--;			// wc will be 0
	
	if (rwc > 0) 
	{		
	    V(&r_sem);		// Wake up 1 reader and pass mutex cascade effect
	} 
else 	if (wwc > 0) 
	{	
	    V(&w_sem);
	} 
else 
	{		
	    V(&mutex);
	}
}



void reader(void)
{ 
	int ID;
	P(&mutex); 
	ID = global_ID++; 
	V(&mutex);
  	while(1)
  	{
		reader_entry(ID);
		printf("[reader #%d]\t****READING****\n", ID);
		sleep(1);
		reader_exit(ID);
  	};
}

void writer(void)
{
  	int ID;
  	P(&mutex); 
  	ID = global_ID++; 
  	V(&mutex);
  	while(1)
  	{
 		writer_entry(ID);
		printf("\t\t\t\t[writer: #%d]\t****WRITING!****\n", ID);
		sleep(1);
		writer_exit(ID);
  	};
}



//-------------------------------------------------------

int main()
{
    int rStart = 4;
    int wStart = 2;
    int i;
    w_sem = CreateSem(0);
    r_sem = CreateSem(0);
    mutex = CreateSem(1);
    
    for(i = 0; i < rStart; i++)
    	start_thread(reader);
    	
    for(i = 0; i < wStart; i++)
    	start_thread(writer);
    
    run();
    while (1) sleep(1);
}
