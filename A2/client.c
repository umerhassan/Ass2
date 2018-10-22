/*
 * ClientSocekt.c
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
#include <strings.h>
#include <netdb.h>
#include <Windows.h>

int main() {

	/* Address initialization */
	struct sockaddr_in server;
	int MYPORTNUM = 12345;
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(MYPORTNUM);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	/* Create the listening socket */
	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		printf("Error in socket() while creating lstn_sock\n");
		exit(-1);
	}

	/* Connect to TCP server */
	int status;
	status = connect(sock, (struct sockaddr *) &server,
			sizeof(struct sockaddr_in));
	if (status < 0) {
		printf("Error in connect()\n");
		exit(-1);
	} else {
		printf("Connected.\n");
	}

	/* Send data*/
	int count;

	while (1) {
		/* Receive data */
		char rcv_message[1024]={"Hi"};
		char message[1024]={"Hi"};
		gets(message); //gets tweet from console
		count = send(sock, message, strlen(message), 0);
		if (count < 0) {
			printf("Error in send()\n");
			exit(-1);
		} 
		count = recv(sock, rcv_message, sizeof(rcv_message), 0);
		if (count < 0) {
			printf("Error in recv()\n");
			exit(-1);
		} 
		printf("Server: %s\n", rcv_message); //Decoded/encoded tweet recieved
		if (strstr(message, "Bye") != NULL) {
			exit(0);
		}
	}

	/* Close the socket */
	close(sock);
	return 0;
}
