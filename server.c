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
		printf("\Client terminated. See you next time!\n");
		handshake();
	}
	if (signo == SIGINT) {
		printf("\nSorry to see you go!\n");
		exit(0);
	}
}

int main() {
	while(1){
		printf("WKP created.\n");
		mkfifo("WKP", 0644);

		printf("Waiting for connection from client...\n");
		int server = open("WKP", O_RDONLY);

		char clientN[32];
    		read(server, clientN, sizeof(clientN));
		printf("Client pipe %s was connected.\n", clientN);
    		remove("WKP");
		printf("WKP removed\n");

    		int client = open(clientN, O_WRONLY);
		printf("Connected to client\n");

		//server reads from client
    		char name[32];
    		read(server, name, sizeof(name));
    		printf("Received client's name: %s.\n", name);

		write(client, name, sizeof(name));
                printf("Acknowledgement sent.\n");
		
		signal(SIGINT, sighandler);
		signal(SIGPIP, sighandler);

		int input = 0;
		int answer = 0;

		while(1){
			read(server, &input, sizeof(input));
			printf("%d", input);
			answer = input * input;
			write(client, &answer, sizeof(answer));
		}
    	}
}
