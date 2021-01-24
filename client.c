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

int solve(int num){
}

int try(int num){
	char output[1024];
	int c;
	read(client, &output, sizeof(output));
	printf("Here is the description for Problem %d:\n%s\n", num, output);
	sleep(1);
        printf("Do you want to try and solve Problem %d?\n", num);
	sleep(0.5);
	printf("(Press 'n' to go back to your problems. Press any other key to continue solving.)\n");
	c = getchar(); // getting whatever scanf left behind
	c = getchar();
	if (c != 'n')
		return -1; // go back
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
	printf("\n---------------------\nWelcome to BleetCode!\n---------------------\n\n");
	sleep(0.5);
	printf("Before we begin...\n");
	sleep(1);
	while(1){
		printf("\nWhat is your name? ");
		scanf(" %32[^\n]", name);
		printf("\nIs your name %s? (Press 'n' to change your name. Press any other key to continue.)\n", name);
		c = getchar(); // getting whatever scanf left behind
		c = getchar();
		if (c != 'n')
			break;
	}
	write(server, name, sizeof(name));

	//client reads from server
    	char message[32];
	read(client, message, sizeof(message));
    	printf("\nHello %s! The handshaking is complete. Let's get started!\n\n", message);

	//client removes pipe
	remove(clientN);
	sleep(1);

	struct problemset *ps = new_set();
	print_set(name, ps);

	int problem_number;

    	while(1){
        	printf("Which problem do you want to attempt? Please enter a number: \n");
        	scanf(" %d", &problem_number);
		write(server, &problem_number, sizeof(problem_number));

		int result;
		result = try(problem_number);
		
		if (result >= 0){
			solve(ps, result);
		}
	}

	return 0;
}
