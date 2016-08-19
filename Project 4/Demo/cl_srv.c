#include "msgs.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Port *ports[100];

int clientPortId;

void client1()
{
	//ports[portNo] = CreatePort(portNo);
	int msg[10], replyPort, i, writeIndex, pktNo, opCode;
	
	replyPort = clientPortId;
	clientPortId++;
	ports[replyPort] = CreatePort(replyPort);
	Port *myPort, *serverPort;
	
	char mystr[10] = "C1_M1";
	serverPort = ports[0];
	writeIndex = 0;
	opCode = 0;
	
	myPort = ports[replyPort];
	printf("\t \t \t \t Starting client listening on port: %d \n", replyPort);
	while(1)
	{
		printf("\t \t \t \t Sending to server on port %d (already known), expecting reply on %d \n", 0, replyPort);
		
		pktNo = 1;
		
		int len = 0;
		
		while(mystr[len] != '\0')
		{
			len++;
		}
		
		msg[0] = replyPort;
		msg[1] = opCode;				//0 for add/replace, 1 for append, 2 for delete, 3 for print
		msg[2] = writeIndex;			//index on table to write to
		msg[3] = ((len-1) / 5) + 1;		//length of the message
		msg[4] = pktNo;				//packet no.
		
		writeIndex = (writeIndex + 2) % 10;
		
		int msgIndex, strIndex;
		
		msgIndex = 5;
		strIndex = 0;
		
		while(mystr[strIndex] != '\0')
		{
			msg[msgIndex] = (int) mystr[strIndex];
			msgIndex++;
			strIndex++;
			
			if(msgIndex == 10 || mystr[strIndex] == '\0')
			{
				if(mystr[strIndex] == '\0')
				{
					msg[msgIndex] = 0;
				}
				
				int m;
				/*
				printf("-----------------message being sent is = ");
				
				for (m = 0; m < 10; m++)
				{
					printf("%d,", msg[m]);
				}
				*/
				Send(&serverPort, msg);
				msgIndex = 5;
				pktNo++;
				msg[4] = pktNo;
				/*
				if(msgIndex == 10)
				{
					Send(&(ports[msg[0]]), msg);
					msgIndex = 5;
					pktNo++;
					msg[4] = pktNo;
				}
							
				if(*(str) == '\0')
				{
					msg[msgIndex] = 0;
					Send(&(ports[msg[0]]), msg);
				}
				*/
			}
		}
		
		int msgId = (int)mystr[len - 1];
		
		msgId = msgId - 48;
		msgId = (msgId + 1) % 10;
		msgId = msgId + 48;
		mystr[len - 1] = (char) msgId;
		
		opCode++;
		opCode = opCode % 3;
		
		//sleep(1);
		Receive(&myPort, msg);
		printf("\t \t \t \t Received on client %d \n \n \n", msg[0]);
		//sleep(1);
	}
}

void client2()
{
	//ports[portNo] = CreatePort(portNo);
	int msg[10], replyPort, i, writeIndex, pktNo, opCode;
	
	replyPort = clientPortId;
	clientPortId++;
	ports[replyPort] = CreatePort(replyPort);
	Port *myPort, *serverPort;
	
	char mystr[10] = "C2_M1";
	serverPort = ports[0];
	writeIndex = 1;
	opCode = 0;
	
	myPort = ports[replyPort];
	printf("\t \t \t \t Starting client listening on port: %d \n", replyPort);
	while(1)
	{
		printf("\t \t \t \t Sending to server on port %d (already known), expecting reply on %d \n", 0, replyPort);
		
		pktNo = 1;
		
		int len = 0;
		
		while(mystr[len] != '\0')
		{
			len++;
		}
		
		msg[0] = replyPort;
		msg[1] = opCode;				//0 for add/replace, 1 for append, 2 for delete, 3 for print
		msg[2] = writeIndex;			//index on table to write to
		msg[3] = ((len-1) / 5) + 1;		//length of the message
		msg[4] = pktNo;				//packet no.
		
		writeIndex = (writeIndex + 2) % 10;
		
		int msgIndex, strIndex;
		
		msgIndex = 5;
		strIndex = 0;
		
		while(mystr[strIndex] != '\0')
		{
			msg[msgIndex] = (int) mystr[strIndex];
			msgIndex++;
			strIndex++;
			
			if(msgIndex == 10 || mystr[strIndex] == '\0')
			{
				if(mystr[strIndex] == '\0')
				{
					msg[msgIndex] = 0;
				}
				Send(&serverPort, msg);
				msgIndex = 5;
				pktNo++;
				msg[4] = pktNo;
			}
		}
		
		int msgId = (int)mystr[len - 1];
		
		msgId = msgId - 48;
		msgId = (msgId + 1) % 10;
		msgId = msgId + 48;
		mystr[len - 1] = (char) msgId;
		
		opCode++;
		opCode = opCode % 3;
		
		//Send(&serverPort, msg);
		sleep(1);
		Receive(&myPort, msg);
		printf("\t \t \t \t Received on client %d \n \n \n", msg[0]);
		sleep(1);
	}
}

void client3()
{
	int msg[10], replyPort, i;
	
	char *str;
	
	replyPort = clientPortId;
	clientPortId++;
	ports[replyPort] = CreatePort(replyPort);
	Port *myPort, *serverPort;
	
	serverPort = ports[0];
	
	//myPort = ports[portNo];
	myPort = ports[replyPort];
	printf("\t \t \t \t Starting client listening on port: %d \n", replyPort);
	
	while(1)
	{
		printf("\t \t \t \t Sending to server on port %d (already known), expecting reply on %d \n", 0, replyPort);
		msg[0] = replyPort; 	//defining the reply port
		msg[1] = 3;
		Send(&serverPort, msg);
		sleep(1);
		
		Receive(&myPort, msg);
		
		printf("\t \t \t \t Printing Table on client \n");
		
		while (msg[1] < 11)
		{
			printf("\t \t \t \t index = %d \t string = ", msg[1]);
			
			int msgIndex;
			msgIndex = 4;
			
			while(msg[msgIndex] != 0)
			{
				printf("%c", (char)msg[msgIndex]);
				msgIndex++;
				
				if(msgIndex == 10)
				{
					msgIndex = 4;
					Receive(&myPort, msg);
				}
			}
			
			printf("\n");
			
			Receive(&myPort, msg);
		}
		
		printf("\t \t \t \t Received on client %d. End of data \n \n \n", msg[0]);
		sleep(1);
	}
}

void server()
{
	char strTable[10][100];
	ports[0] = CreatePort(0);
	Port *myPort;
	int msg[10], i;
	myPort = ports[0];
	int pkt;
	
	//printf("\t \t \t \t Starting server listening on port: %d \n", portNo);
	printf("\t \t \t \t Starting server listening on port: %d \n", 0);
	
	//Initializing the strTable
	for(i = 0; i < 10; i++)
	{
		strTable[i][0] = '\0';
	}
	
	while(1)
	{
		Receive(&myPort, msg);
		printf(" \n \t \t \t \t Received on server (reply port = %d) \n", msg[0]);
		
		//sleep(1);
		printf(" \n \t \t \t \t Received String = ");
		
		for(i = 0; i < 10; i++)
			printf("%d,", msg[i]);
		
		for(i = 5; i < 10; i++)
		{
			printf("%c", msg[i]);
		}
		printf("\n");
		
		if(msg[1] == 3)		//print
		{
			int msgIndex;
			for(i = 0; i < 10; i++)
			{
				if(strTable[i][0] != '\0')		//only send those strings that have a value
				{
					msgIndex = 1;
					int pktNo = 1;
					int len = 0;
		
					while(strTable[i][len] != '\0')
					{
						len++;
					}
					
					msg[msgIndex] = i;		// index of string
					msgIndex++;
					
					msg[msgIndex] = (len / 6) + 1;	// length of the message
					msgIndex++;
					
					int pktInfoIndex;
					msg[msgIndex] = pktNo;
					pktInfoIndex = msgIndex;	// packet index of message
					msgIndex++;
					
					int msgBodyBase;
					msgBodyBase = msgIndex;		// recording base index for message body
					
					char *str;
					str = strTable[i];
					
					while(*(str) != '\0')
					{
						msg[msgIndex] = (int)(*str);
						str++;
						msgIndex++;
						
						if(msgIndex == 10 || *(str) == '\0')
						{
							if(msgIndex == 10)
							{
								Send(&(ports[msg[0]]), msg);
								msgIndex = msgBodyBase;
								pkt++;
								msg[pktInfoIndex] = pkt;
							}
							
							if(*(str) == '\0')
							{
								msg[msgIndex] = 0;
								Send(&(ports[msg[0]]), msg);
							}
						}
					}
				}
			}
			
			msg[1] = 11;
			
			Send(&(ports[msg[0]]), msg);
			
		} else
		{
			char *str;
			str = strTable[(msg[2])];
			
			if (msg[1] == 2)		//delete
			{
				if (*(str) != '\0')
				{
					*(str) = '\0';
				}
				
				Send(&(ports[msg[0]]), msg);
				
			}else if (msg[1] == 1 || msg[4] > 1)		//append
			{
				while(*(str) != '\0')
				{
					str++;
				}
				
				for(i = 5; msg[i] != 0 && i < 10; i++)
				{
					*(str) = (char)msg[i];
					str++;
				}
				
				*(str) = '\0';
				
				Send(&(ports[msg[0]]), msg);
				
			}else if (msg[1] == 0)		//add/replace
			{
				for(i = 5; msg[i] != 0 && i < 10; i++)
				{
					*(str) = (char)msg[i];
					str++;
				}
				
				*(str) = '\0';
				
				Send(&(ports[msg[0]]), msg);
			}
		}
		
		printf(" \n \t \t \t \t the string table on server now is\n");
		
		for(i = 0; i < 10; i++)
		{
			printf(" \t \t \t \t %d: \t %s \n", i, strTable[i]);
		}
		
	}
}

void main()
{
	//portMutex = CreateSem(1);		//For strategy 1
	clientPortId = 11;
	start_thread(server);
	start_thread(client1);
	start_thread(client2);
	start_thread(client3);
	//start_thread(client);
	
	run();
    	while (1) sleep(1);
}
