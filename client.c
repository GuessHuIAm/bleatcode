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

void remove_files(){
	int f = fork();
	if (!f){
		char *cmd = "rm";
		char *argv[3];
		argv[0] = "rm";
		argv[1] = "file*";
		argv[2] = NULL;
		execvp(cmd, argv);
		return;
	}
	else
		return;
}

int solve_prob(int client, int server, int num){
	int status;
	int f = fork();
	if (!f){
		int pid = getpid();
		char *cmd = "nano";
		char *argv[3];
		argv[0] = "nano";
		sprintf(argv[1], "file%d.c", num);
		argv[2] = NULL;
		return execvp(cmd, argv);
	}
	else{
		int pid = wait(&status);
		printf("\nWelcome back! Let's test your code.\n");
	}
	return 100;
}

int try(int client, int server, int num){
	char output[1024];
	int c;
	read(client, &output, sizeof(output));
	printf("\nHere is the description for Problem %d:\n%s\n", num, output);
	sleep(1);
        printf("Do you want to try and solve Problem %d?\n", num);
	sleep(0.5);
	printf("(Press 'n' to go back to see your problems. Press any other key to continue solving.)\n");
	c = getchar(); // getting whatever scanf left behind
	c = getchar();
	if (c == 'n')
		return -1; // go back
	int s = num;
	while (s >= 0 && s < 20){
		sleep(2);
		printf("Solving... \n");
		sleep(1);
		s = solve_prob(client, server, num);
	}
	if (s == 100){ // success
		sleep(1);
		printf("Yay! You did it--Problem %d marked complete.", num);
		sleep(1);
		printf("Let's go back to your problem set.");
		sleep(1);
		return num;
	}
	if (s < 0) // giving up
		return -10;
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

	int problem_number;

    	while(1){
		print_set(name, ps);
        	printf("Which problem do you want to attempt? Please enter a number: ");
        	scanf(" %d", &problem_number);
		write(server, &problem_number, sizeof(problem_number));

		int result;
		result = try(client, server, problem_number);

		if (result >= 0){
			solve(ps, result);
		}
		else if (result == -10){
		printf("Would you like to continue solving problems? (Press 'n' to leave BleetCode. Press any other key to go back to your problem set.)\n");
		c = getchar(); // getting whatever scanf left behind
		c = getchar();
		if (c == 'n')
			break;
		}
	}
	printf("Sorry to see you go! Remember your ID is __ so you can continue solving next time!\n");
	remove_files();
	return 0;
}
