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
static char word[200][200];
static char hash[200][200];
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

		
		int count;
	
		while (1) {
			/* Receive data */
			char rcv_message[1024]={"Hi"};
			char message[1024]={"0x "};
			
			recv(connected_sock, rcv_message, sizeof(rcv_message), 0);
			
			char copyRcv[1024];
			strcpy(copyRcv,rcv_message);
			
			if(strstr(rcv_message, "0x") == NULL) {
			char *p = strtok (rcv_message, " ");
			while (p != NULL)
			{
				int ascii=0;
				for(int i=0;i<strlen(p);i++)
					ascii = ascii + (int)p[i];
				printf("Storing in %d: %s with ascii %d\n",numberOfWords,p,ascii);
				strcpy(word[numberOfWords],p);
				char x[1024];
				sprintf(x, "%d", ascii);
				strcpy(hash[numberOfWords],x);
				numberOfWords++;

				p = strtok (NULL, " ");
			}
		
			char *b = strtok (copyRcv, " ");
			while (b != NULL)
			{
				for(int i = 0; i < 10; i++){
					printf("b is: %s, word[%d]: %s\n",b,i,word[i]);

					if(strcmp(b,word[i])==0){
						strcat(message,hash[i]);
						strcat(message," ");
						break;
					}
				}
					
				printf("b: %s\n",b);
				b = strtok (NULL, " ");
			}
			
			for(int i = 0; i < 10; i++)
				printf("Word[%d]: %s\n",i,word[i]);
			for(int i = 0; i < 10; i++)
				printf("Hash[%d]: %s\n",i,hash[i]);
			
			} else{
				
				char *b = strtok (copyRcv, " ");
				while (b != NULL)
				{
					b = strtok (NULL, " ");
					if(b!= NULL){
						for(int i = 0; i < 10; i++){
							printf("hahhah b is: %s, hash[%d]: %s\n",b,i,hash[i]);

							if(strcmp(b,hash[i])==0){
								strcat(message,word[i]);
								strcat(message," ");
								break;
							}
						}
					}
					printf("message is: %s",message);
				}
				
				
			}
		/*	for(int i = 0; i < 10; i++){
				printf("Word[%d]: %s\n",i,word[i]);
				if(strcmp(rcv_message,word[i])==0){
				  printf("Hash[%d]: %s\n",i,hash[i]);
				  strcpy(message,hash[i]);
				  send(connected_sock, message, strlen(message), 0);
				  break;
				}
			}
			for(int i = 0; i < 10; i++){
				printf("Hash[%d]: %s\n",i,hash[i]);
				if(strcmp(rcv_message,hash[i])==0){
				  printf("Word[%d]: %s\n",i,word[i]);
				  strcpy(message,word[i]);
				  send(connected_sock, message, strlen(message), 0);
				  break;
				}
			}
			*/
			
			send(connected_sock, message, strlen(message), 0);
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
