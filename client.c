#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "problem.h"
#include "problemset.h"
#include "csv.h"

static void sighandler(int signo) {
	if (signo == SIGINT) {
		printf("\nSorry to see you go--your progress was not saved! Good luck next time!\n");
		exit(0);
	}
	if (signo == SIGTSTP) {
		printf("\nSorry to see you go--your progress was not saved! Good luck next time!!\n");
		exit(0);
	}
	if (signo == SIGPIPE) {
		printf("\nServer terminated--your progress was not saved. Good luck next time!\n");
		exit(0);
	}
}

int get_char(){
	int c;
	do {
		c = getchar();
	}while(c == '\n');
	int o;
	while ((o = getchar()) != '\n' && o != EOF) { } // remove other stuff
	return c;
}

int get_problem_number(){
	int number;
	scanf(" %d", &number);
	while (number < 0 || n > 19){
		printf("Please enter a number between 0 and 19: "); 
		scanf(" %d", &number);
	}
	return number;
}

int get_id(){
	int id;
	if (scanf(" %d", &id) == 1)
		return id;
	else
		printf("Please enter a valid ID number: ");
}

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

void handshake(){
	//Client makes FIFO and sends name to server
	char clientN[32];
	sprintf(clientN, "%d", getpid());
	mkfifo(clientN, 0644);

	int server = open("WKP", O_WRONLY);
    	write(server, clientN, sizeof(clientN));

	int client = open(clientN, O_RDONLY);

	printf("Loading...\n");

	//Client receives server's response, remove the FIFO
	printf("Loaded!\n");
	char hello[256];
	read(client, hello, sizeof(hello));
	printf("%s\n", hello);
	remove(clientN);

	//Client sends response to server
	write(server, "Handshake now complete!\n", sizeof("Handshake now complete!\n"));

	close(server);
	close(client);
	return;
}

void find_name(int server, int client, char *name){
	//Client's intro, send username to server
	printf("\n---------------------\nWelcome to BleatCode!\n---------------------\n\n");
	sleep(0.5);
	printf("Two more things before we begin!\n");
	sleep(1);

	int c;
	int s = 1; // selector int for communication
	while(1){
		printf("What is your name? ");
		scanf(" %32[^\n]", name);
		sleep(0.5);
		printf("\nIs your name %s? (Press 'n' to change your name. Press any other key to continue.)\n", name);
		do{
			c = get_char(c);
		} while (c == '\n');
		if (c != 'n')
			break;
	}
	write(server, &s, sizeof(s)); //Let server know that this is a name request
	write(server, name, sizeof(name));

	//server returns your name
    	char message[32];
	read(client, message, sizeof(message));
    	printf("\nHello %s!\n", message);

	sleep(1);
	return;
}

int find_id(int server, int client){
	int id;
	int nextid = nextPS();
	printf("\nDo you have a user ID from the last time you visited Bleat?\n");
	printf("(Press 'y' to enter your ID. Press any other key to receive a new ID.)\n");
	int c = get_char();
	if (c == 'y'){
		printf("Please enter your ID: ");
		id = get_id();
		if (id >= nextid){
			printf("The system couldn't find your ID. Your new ID is %d.\n", nextid);
			return nextid;
		}
		else return id;
	}
	else{
		printf("Your new ID is %d.\n", nextid);
		return nextid;
	}
}

struct problemset *find_set(int id){
	struct problemset *ps;
	int nextid = nextPS();
	if (id >= nextid){
		ps = new_set(id);
	}
	else {
		ps = retrieve_set(id);
	}
	return ps;
}

int test(int client, int server, char *file_name, int num){
	int s; // communicator to server
	// write(server, &s, sizeof(s)); // request for problem description
	// write(server, &problem_number, sizeof(problem_number));
	return -1;
}

void forking(char *fn){
	int status;
	int f = fork();
	if (!f){
		int pid = getpid();                                                                                                             //      char *cmd = "nano";
       		char *argv[3];
      		argv[0] = "nano";
        	argv[1] = fn;
        	argv[2] = NULL;
        	execvp(argv[0], argv);
		exit(0);
	}
	else{
		int pid = wait(&status);
		pid = WEXITSTATUS(status);
		printf("Editing!\n\n");
		sleep(1);
	}
}
	//else if (child_pid > 0){ // Parent
	//	int status;
	//	wait(&status);
	//	return;}

int solve_prob(int client, int server, int num){
	char fn[100];
	sprintf(fn, "file%d.c", num);
	if (access(fn, F_OK) != 0){ // if this file does not exist
		int s = 2; // communicator to server signal
		write(server, &s, sizeof(s)); // request for edit file initiation
		write(server, fn, sizeof(fn)); // send edit file name
		write(server, &num, sizeof(num)); // sending problem number

		// reading message and then adding it onto the new file
		char message[1024];
		read(client, message, sizeof(message));

		FILE* file = fopen(fn, "w");
		// exiting program
		if (file == NULL) {
			printf("Error!\n");
		}
		fprintf(file, "%s", message);
		fclose(file);
	}
	forking(fn); // forking to edit in nano
	
	printf("Welcome back! Let's test your code.\n");
	int test_result = test(server, client, fn, num);
	// send to server and back and forth, if the solutions all match, break so this func returns 100
	if (test_result < 0){
		printf("Would you like to continue editing your code?\n");
		printf("(Press 'n' to go back to your problem set. Press any other key to continue editing.)\n");
		int c;
		c = get_char(c);
		if (c == 'n')
			return -1; // go back
		return num; // continue editing
	}
	else
		return 100;
}

int try(int client, int server, int num){
	int c;
	//read(client, &output, sizeof(output));
	printf("\nHere is the description for Problem %d:\n", num);
	printf("%s ", subject(num));
	printf("- %s \n", get_func(num));
	printf("%s\n", descriptor(num));
	sleep(1);
        printf("Do you want to try and solve Problem %d?\n", num);
	printf("(Press 'n' to go back to see your problems. Press any other key to continue solving.) ");
	sleep(1);
	c = get_char(c);
	if (c == 'n')
		return -1; // go back
	int s = num;
	while (s >= 0 && s < 20){
		sleep(2);
		s = solve_prob(client, server, num);
	}
	if (s == 100){ // success
		sleep(1);
		printf("Yay! You did it--Problem %d marked complete.\n", num);
		sleep(1);
		printf("Let's go back to your problem set.\n");
		sleep(1);
		return num;
	}
	if (s < 0) // giving up
		return -10;
}

int main(){
	signal(SIGINT, sighandler);
	signal(SIGTSTP, sighandler);
	signal(SIGPIPE, sighandler);
	handshake();

	int server = open("serverpipe", O_WRONLY);
	int client = open("clientpipe", O_RDONLY);

	char name[32];
	find_name(server, client, name);
	int user_id = find_id(server, client);
	struct problemset *ps = find_set(user_id);

	int problem_number;
	int c;
    	while(1){
		print_set(name, ps);
        	printf("\nWhich problem do you want to attempt? Please enter a number: ");
        	problem_number = get_problem_number();

		int result;
		result = try(client, server, problem_number);

		if (result >= 0){
			solve(ps, result); // updating problem set with completion status
		}
		else if (result == -10){
			printf("Would you like to continue solving problems?\n");
			printf("(Press 'n' to leave BleatCode. Press any other key to go back to your problem set.)\n");
			c = get_char(c);
			if (c == 'n'){
				update_user(ps, user_id);
				printf("Sorry to see you go! Progress saved. Remember your ID (%d) so you can continue solving next time!\n", user_id);
				free(ps);
				remove_files();
				return 0;
			}
		}
	}
	update_user(ps, user_id);
	printf("Sorry to see you go! Progress saved. Remember your ID (%d) so you can continue solving next time!\n", user_id);
	free(ps);
	return 0;
}
