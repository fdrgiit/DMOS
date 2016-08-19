/*
Project 3 strategy 2
Name: Abhinav Singh
ASU ID: 1206277744
*/

#include "msgs.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct Ports *portsnum[100];

int sendport;

void server()
{
	portsnum[0] = Initialize(0);
	struct Ports *port1;
	int msg[10];
	port1 = portsnum[0];
	
	printf("\t \t \t \t \t Starting server listening on port: %d \n", 0);
	
	while (1)
	{
		Receive(&port1, msg);
		printf(" \n \t \t \t \t \t Received on server (Reciever Port = %d) \n\n", msg[0]);
		sleep(1);
		printf("Processing \n");
		printf("Sending to client on port number: %d \n", msg[0]);
		Send(&(portsnum[msg[0]]), msg);
		sleep(1);
	}
}


void client()
{
	int msg[10], recvport;
	
	recvport = sendport;
	sendport++;
	portsnum[recvport] = Initialize(recvport);
	struct Ports *port2, *serverPort;
	
	serverPort = portsnum[0];
	
	port2 = portsnum[recvport];
	printf("\t \t \t \t \t Starting client listening on port: %d \n", recvport);
	while(1)
	{
		printf("\t \t \t \t \t Sending to server on port %d (already known), expecting reply on %d \n", 0, recvport);
		msg[0] = recvport; //defining the reciever port
		Send(&serverPort, msg);
		sleep(1);
		Receive(&port2, msg);
		printf("\t \t \t \t \t Received on client %d \n \n \n", msg[0]);
		sleep(1);
	}
}

int main()
{
	sendport = 11;
	start_thread(server);
	start_thread(client);
	start_thread(client);
	start_thread(client);
	start_thread(client);
	run();
	return 0;
}
