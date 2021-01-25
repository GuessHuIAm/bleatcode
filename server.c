#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>
#include "problem.h"
#include "problemset.h"
#include "csv.h"

static void sighandler(int signo) {
	if (signo == SIGPIPE) {
		printf("\nClient terminated. See you next time!\n");
		remove("serverpipe");
		remove("clientpipe");
		exit(0);
	}
	if (signo == SIGINT) {
		printf("\nSorry to see you go!\n");
		remove("serverpipe");
		remove("clientpipe");
		exit(0);
	}
	if (signo == SIGTSTP) {
		printf("\nSorry to see you go!\n");
		remove("serverpipe");
		remove("clientpipe");
		exit(0);
	}
}

void handshake(){
	//Server creates WKP and receives the client's PID
	printf("Waiting for client connection...\n");
	mkfifo("WKP", 0644);
	int server = open("WKP", O_RDONLY);
	char clientN[32];
	read(server, clientN, sizeof(clientN));
	printf("Client pipe %s was connected.\n", clientN);
	remove("WKP");
	
	//Server writes back to client
	int client = open(clientN, O_WRONLY);
	printf("Connected to client.\n");
    	char message[] = "The handshake is complete. Let's get started!\n";
    	write(server, message, sizeof(message));
    	printf("Sent welcome message to client %s.\n", message);
	     
	//Server receives client's message
	char handshake[256];
    	read(server, handshake, sizeof(handshake));
    	printf("From the client: %s\n", handshake);
	close(client);
    	close(server);
	     
	return;
}

int main() {
	mkfifo("serverpipe", 0644);
	mkfifo("clientpipe", 0644);
	signal(SIGINT, sighandler);
	signal(SIGPIPE, sighandler);
	signal(SIGTSTP, sighandler);
	handshake();

	int server = open("serverpipe", O_RDONLY);
	int client = open("clientpipe", O_WRONLY);
	
	int s;
	char name[32];
	while(1){
		read(server, &s, sizeof(s)); // reads communicator integer
		if (s == 1){ // request to give name
			read(server, name, sizeof(name));
			printf("Received client's name: %s.\n", name);
			write(client, name, sizeof(name));
			printf("Acknowledgement sent.\n");
		}
		//else if (s == 2){ // request for problem set search
		//}
		//else if (s == 3){ // request for solution check
		//}
		//else if (s == 4){ // request to solve the 
		//}
		//else if (s == 5){ 
		//}
	}
	return 0;
}
