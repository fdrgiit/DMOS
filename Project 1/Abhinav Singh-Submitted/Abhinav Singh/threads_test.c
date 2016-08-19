#include<stdlib.h>
#include <stdio.h>
#include "threads.h"
#define SLEEP_TIME 1
 
int global = 0;
int ID = 1;
 
 
void function() 
{
	printf("Function starting for the 1st Time\n");
	fflush(stdout);
	int local = 0;
	int lID = ID++;
	
	while(1)
	{
		printf("Function %d Running\n",lID);
		sleep(SLEEP_TIME);
		yield();
		printf("Function %d Incrementing the Local Value = %d and Global Value = %d\n",lID,local++,global++);
		sleep(SLEEP_TIME);
		printf("Function %d Yields\n",lID);
		yield();
	}
	
	printf("Function %d Exits\n",lID);
	exitFunction(&Q);
}
 
int main()
{
	Q = initQ();
	start_thread(function);
	start_thread(function);
	start_thread(function);
	printQ(Q);
	run();
}
