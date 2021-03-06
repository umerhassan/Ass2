/*
 * ServerSocket.c
 *
 *  Created on: Sep 13, 2018
 *      Author: reza
 */

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <string.h>

#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <netdb.h>
static char words[200][200];
static char hashes[200][200];
int numberOfWords = 0;
int main() {

	/* Address initialization */
	struct sockaddr_in server;
	int MYPORTNUM = 12345;
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(MYPORTNUM);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	/* Create the listening socket */
	int lstn_sock;
	lstn_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (lstn_sock < 0) {
		printf("Error in socket() while creating lstn_sock\n");
		exit(-1);
	}
	printf("Socket created successfully.\n");

	/* Bind the socket to address and port */
	int status;
	status = bind(lstn_sock, (struct sockaddr *) &server,
			sizeof(struct sockaddr_in));
	if (status < 0) {
		printf("Error in bind()\n");
		exit(-1);
	}
	printf("Binding completed.\n");

	/* Connect to TCP server */
	status = listen(lstn_sock, 5);
	if (status < 0) {
		printf("Error in listen()\n");
		exit(-1);
	}
	printf("Listening for connection requests...\n");

	/* Main Loop for listening */
	while (1) {

		/* Accept a connection */
		int connected_sock;
		connected_sock = accept(lstn_sock, NULL,
		NULL);
		if (connected_sock < 0) {
			printf("Error in accept()\n");
			exit(-1);
		}
		printf("Connection established.\n");

		/* Send data*/
		int count;
		

		/* Receive data */
		char rcv_message[1024];
		while (1) {
			
			count = recv(connected_sock, rcv_message, sizeof(rcv_message), 0);
			if (count < 0) {
				printf("Error in recv()\n");
			} 
			else {
				printf("Client said: %s\n", rcv_message);
		
				
				//if the word is not hashed
				int ascii=0;
				for(int i=0;i<strlen(rcv_message);i++)
					ascii = ascii + (int)rcv_message[i];
				
				char message[102400] ;
				sprintf(message, "%d", ascii); //convert ascii value to string
				
				 strcpy(words[numberOfWords], rcv_message);
				 strcpy(hashes[numberOfWords], message);
				 numberOfWords++;
				printf("\nAscii is %d , message is %s\n",ascii,message);
				count = send(connected_sock, message, sizeof(message), 0);
				if (count < 0) {
					printf("Error in send()\n");
				}
			}
			
			if (strstr(rcv_message, "Bye") != NULL) {
				exit(0);
			}
		}


		close(connected_sock);
		exit(0);


	}
	/* Close the socket */
	close(lstn_sock);
	return 0;
}

