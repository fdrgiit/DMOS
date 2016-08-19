/*
NAME: ABHINAV SINGH 
ASU ID: 1206277744
*/

#include "msgs.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

struct Ports *ports[100];

int clientPortId;

void client1()
{
	int comm[10], note, wordindex, initNo, operation;
	
	note = clientPortId;
	clientPortId++;
	ports[note] = Initialize(note);
	struct Ports *opPort, *headerPort;
	
	char threads[10] = "C1_M1";
	headerPort = ports[0];
	wordindex = 0;
	operation = 0;
	
	opPort = ports[note];
	printf("Starting client communication on port: %d \n", note);
	while(1)
	{
		printf("Sending to server on port %d, wait for reply on %d \n", 0, note);
		
		initNo = 1;
		
		int len = 0;
		
		while(threads[len] != '\0')
		{
			len++;
		}
		
		comm[0] = note;
		comm[1] = operation;			//0 for add/replace, 1 for append, 2 for delete, 3 for print
		comm[2] = wordindex;			
		comm[3] = ((len-1) / 5) + 1;		
		comm[4] = initNo;		
		
		wordindex = (wordindex + 2) % 10;
		
		int msgIndex, strIndex;
		
		msgIndex = 5;
		strIndex = 0;
		
		while(threads[strIndex] != '\0')
		{
			comm[msgIndex] = (int) threads[strIndex];
			msgIndex++;
			strIndex++;
			
			if(msgIndex == 10 || threads[strIndex] == '\0')
			{
				if(threads[strIndex] == '\0')
				{
					comm[msgIndex] = 0;
				}

				Send(&headerPort, comm);
				msgIndex = 5;
				initNo++;
				comm[4] = initNo;
			}
		}
		
		int msgId = (int)threads[len - 1];
		
		msgId = msgId - 48;
		msgId = (msgId + 1) % 10;
		msgId = msgId + 48;
		threads[len - 1] = (char) msgId;
		
		operation++;
		operation = operation % 3;

		Receive(&opPort, comm);
		printf("\nReceived on client %d \n \n", comm[0]);

	}
}

void client2()
{

	int comm[10], note, wordindex, initNo, operation;
	
	note = clientPortId;
	clientPortId++;
	ports[note] = Initialize(note);
	struct Ports *opPort, *headerPort;
	
	char threads[10] = "C2_M1";
	headerPort = ports[0];
	wordindex = 1;
	operation = 0;
	
	opPort = ports[note];
	printf("Starting client communication on port: %d \n", note);
	while(1)
	{
		printf("Sending to server on port %d, wait for reply on %d \n", 0, note);
		
		initNo = 1;
		
		int len = 0;
		
		while(threads[len] != '\0')
		{
			len++;
		}
		
		comm[0] = note;
		comm[1] = operation;				//0 for add/replace, 1 for append, 2 for delete, 3 for print
		comm[2] = wordindex;			//index on table to write to
		comm[3] = ((len-1) / 5) + 1;		//length of the message
		comm[4] = initNo;				//packet no.
		
		wordindex = (wordindex + 2) % 10;
		
		int msgIndex, strIndex;
		
		msgIndex = 5;
		strIndex = 0;
		
		while(threads[strIndex] != '\0')
		{
			comm[msgIndex] = (int) threads[strIndex];
			msgIndex++;
			strIndex++;
			
			if(msgIndex == 10 || threads[strIndex] == '\0')
			{
				if(threads[strIndex] == '\0')
				{
					comm[msgIndex] = 0;
				}
				Send(&headerPort, comm);
				msgIndex = 5;
				initNo++;
				comm[4] = initNo;
			}
		}
		
		int msgId = (int)threads[len - 1];
		
		msgId = msgId - 48;
		msgId = (msgId + 1) % 10;
		msgId = msgId + 48;
		threads[len - 1] = (char) msgId;
		
		operation++;
		operation = operation % 3;
		
		sleep(1);
		Receive(&opPort, comm);
		printf("\nReceived on client %d \n \n \n", comm[0]);
		sleep(1);
	}
}

void client3()
{
	int comm[10], note;
	note = clientPortId;
	clientPortId++;
	ports[note] = Initialize(note);
	struct Ports *opPort, *headerPort;
	headerPort = ports[0];
	opPort = ports[note];

	printf("Starting client communication on port: %d \n", note);
	
	while(1)
	{
		printf("Sending to server on port %d, wait for reply on %d \n", 0, note);
		comm[0] = note; 	
		comm[1] = 3;
		Send(&headerPort, comm);
		sleep(1);
		
		Receive(&opPort, comm);
		
		while (comm[1] < 11)
		{
			int msgIndex;
			msgIndex = 4;
			
			while(comm[msgIndex] != 0)
			{
				msgIndex++;
				
				if(msgIndex == 10)
				{
					msgIndex = 4;
					Receive(&opPort, comm);
				}
			}
			
			printf("\n");
			
			Receive(&opPort, comm);
		}
		
		printf("\nReceived on client %d. End of data. \n \n \n", comm[0]);
		sleep(1);
	}
}

void server()
{
	char strTable[10][100];
	ports[0] = Initialize(0);
	struct Ports *opPort;
	int comm[10], i;
	opPort = ports[0];
	int pkt;
	
	printf("Starting server communication on port: %d \n", 0);
	
	for(i = 0; i < 10; i++)	//Initializing the Table
	{
		strTable[i][0] = '\0';
	}
	
	while(1)
	{
		Receive(&opPort, comm);
		printf(" \nReceived on server (Port No. = %d) \n", comm[0]);
		
		printf(" \nReceived String = ");
		
		for(i = 0; i < 10; i++)
		{
			printf("%d,", comm[i]);
		}
		
		for(i = 5; i < 10; i++)
		{
			printf("%c", comm[i]);
		}
		printf("\n");
		
		if(comm[1] == 3)		
		{
			int msgIndex;
			for(i = 0; i < 10; i++)
			{
				if(strTable[i][0] != '\0')		
				{
					msgIndex = 1;
					int initNo = 1;
					int len = 0;
		
					while(strTable[i][len] != '\0')
					{
						len++;
					}
					
					comm[msgIndex] = i;		// index of string
					msgIndex++;
					
					comm[msgIndex] = (len / 6) + 1;	// length of the message
					msgIndex++;
					
					int pktInfoIndex;
					comm[msgIndex] = initNo;
					pktInfoIndex = msgIndex;	
					msgIndex++;
					
					int msgBodyBase;
					msgBodyBase = msgIndex;		
					
					char *str;
					str = strTable[i];
					
					while(*(str) != '\0')
					{
						comm[msgIndex] = (int)(*str);
						str++;
						msgIndex++;
						
						if(msgIndex == 10 || *(str) == '\0')
						{
							if(msgIndex == 10)
							{
								Send(&(ports[comm[0]]), comm);
								msgIndex = msgBodyBase;
								pkt++;
								comm[pktInfoIndex] = pkt;
							}
							
							if(*(str) == '\0')
							{
								comm[msgIndex] = 0;
								Send(&(ports[comm[0]]), comm);
							}
						}
					}
				}
			}
			
			comm[1] = 11;
			
			Send(&(ports[comm[0]]), comm);
			
		} else
		{
			char *str;
			str = strTable[(comm[2])];
			
			if (comm[1] == 2)		//delete
			{
				if (*(str) != '\0')
				{
					*(str) = '\0';
				}
				
				Send(&(ports[comm[0]]), comm);
				
			}
			else if (comm[1] == 1 || comm[4] > 1)		//append
			{
				while(*(str) != '\0')
				{
					str++;
				}
				
				for(i = 5; comm[i] != 0 && i < 10; i++)
				{
					*(str) = (char)comm[i];
					str++;
				}
				
				*(str) = '\0';
				
				Send(&(ports[comm[0]]), comm);
				
			}
			else if (comm[1] == 0)		//add/replace
			{
				for(i = 5; comm[i] != 0 && i < 10; i++)
				{
					*(str) = (char)comm[i];
					str++;
				}
				
				*(str) = '\0';
				
				Send(&(ports[comm[0]]), comm);
			}
		}
		
		printf(" \nThe Table on the Server is:\n");
		
		for(i = 0; i < 10; i++)
		{
			printf(" %d: \t %s \n", i, strTable[i]);
		}
		
	}
}

int main()
{
	clientPortId = 11;
	start_thread(server);
	start_thread(client1);
	start_thread(client2);
	start_thread(client3);
	run();
    	
	while (1) 
	{
		sleep(1);
	}

}	
