#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
//#include "problemset.h"

void printproblems(){
	printf("Problem #     Type          Completed?\n");
	printf("%7d%11d%10d\n", 1, 1222, 9348);
	printf("%7d%11d%10d\n", 2, 2111, 214);
}

int main(){
	//client to server handshake
	char clientN[32];
	sprintf(clientN, "%d", getpid());
	mkfifo(clientN, 0644);

	//client to server
    	int server = open("WKP", O_WRONLY);
    	write(server, clientN, sizeof(clientN));
	printf("Waiting for connection...\n");

	int client = open(clientN, O_RDONLY);
	printf("Server connected to client.\n");

	//client reads from server
    	char message[32];
	read(client, message, sizeof(message));
    	printf("Hello %s!\n", message);

	//client removes pipe
	remove(clientN);

	//client sends back to server
    	write(server, "Hello!", sizeof("Hello!"));
	printf("Client sent <Hello!>, the handshake is complete!\n");

	int input;
	int output;

    	while(1){
		printproblems();
        	printf("Which problem do you want to attempt? Please enter a number: \n");
        	scanf("%d", &input);
		write(server, &input, sizeof(input));

		read(client, &output, sizeof(output));
        	printf("Do you want to solve this? %d\n", input, output);
 	}

	return 0;
}
