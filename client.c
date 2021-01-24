#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "problem.h"
#include "problemset.h"
#include "csv.h"

int main(){
	//client to server handshake
	char clientN[32];
	sprintf(clientN, "%d", getpid());
	mkfifo(clientN, 0644);

	//client to server
    	int server = open("WKP", O_WRONLY);
    	write(server, clientN, sizeof(clientN));
	printf("Loading...\n");

	int client = open(clientN, O_RDONLY);
	printf("Loaded!\n");

	//client's intro / send user name to server
	char name[32];
	int c;
	printf("Welcome to BleetCode!\n");
	sleep(0.5);
	printf("Before we begin...\n");
	sleep(1);
	while(1){
		printf("What is your name?\n");
		scanf(" %32[^\n]", name);
		printf("Is your name %s? (Press 'n' to change your name. Press any other key to continue.)\n", name);
		c = getchar(); // getting whatever scanf left behind
		c = getchar();
		if (c != 'n')
			break;
	}
	write(server, name, sizeof(name));

	//client reads from server
    	char message[32];
	read(client, message, sizeof(message));
    	printf("Hello %s! The handshaking is complete. Let's get started!\n", message);

	//client removes pipe
	remove(clientN);
	sleep(1);

	//client sends back to server
    	write(server, "Hello!", sizeof("Hello!"));

	struct problemset *ps = new_set();
	print_set(ps);

	int input;
	int output;

    	while(1){
		//print_set(ps);
        	printf("Which problem do you want to attempt? Please enter a number: \n");
        	scanf("%d", &input);
		write(server, &input, sizeof(input));

		read(client, &output, sizeof(output));
        	printf("Do you want to solve Problem %d?\n", input);

		int status;
		int f = fork();
		if (!f){
			int pid = getpid();
			char *cmd = "nano";
			char *argv[3];
			argv[0] = "nano";
			argv[1] = "file.c";
			argv[2] = NULL;
			return execvp(cmd, argv);
		}
		else{
			int pid = wait(&status);
			printf("\nParent: The child with pid %d has finished! It slepted for %d seconds.\n", pid, WEXITSTATUS(status));
			printf("\nParent: This parent process is finished. Bye!\n");
		}
	}

	return 0;
}
