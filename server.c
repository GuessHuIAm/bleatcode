#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include "problem.h"
#include "problemset.h"
#include "csv.h"

void handshake(){
	//Server creates WKP and receives the client's PID
	printf("\nWaiting for client connection...\n");
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
    	write(client, message, sizeof(message));
    	printf("Sent welcome message to client %s.\n", clientN);

	//Server receives client's message
	char handshake[256];
    	read(server, handshake, sizeof(handshake));
    	printf("From the client: %s\n", handshake);
	close(client);
    	close(server);

	return;
}

static void sighandler(int signo) {
	if (signo == SIGPIPE) {
		printf("\nClient terminated. See you next time!\n");
		remove("serverpipe");
		remove("clientpipe");
		remove("WKP");
		handshake();
	}
	if (signo == SIGINT) {
		printf("\nSorry to see you go!\n");
		remove("WKP");
		remove("serverpipe");
		remove("clientpipe");
		exit(0);
	}
	if (signo == SIGTSTP) {
		printf("\nSorry to see you go!\n");
		remove("WKP");
		remove("serverpipe");
		remove("clientpipe");
		exit(0);
	}
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
		else if (s == 2){ // request for edit file initiation
			char fn[100];
			char message[1024];
			int num;
			read(server, fn, sizeof(fn));
			read(server, &num, sizeof(num));
			printf("Received file <%s> for Problem %d. Will process now!\n", fn, num);
			char type[32];
			strcpy(type, get_type(num));
			char func_name[32];
			strcpy(func_name, get_func(num));
			char parameters[64];
			strcpy(parameters, get_para(num));
			char type2[32];
			strcpy(type2, get_type2(num));
			char tc1[32];
			strcpy(tc1, get_tc1(num));
			char tc2[32];
			strcpy(tc2, get_tc2(num));
			char tc3[32];
			strcpy(tc3, get_tc3(num));
			sprintf(message, "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n%s %s(%s){\n\t// Write your code here!\n}\n\nint main(){\n\t// Don't touch the test cases here!\n\tFILE *fn = fopen(\"solution.txt\",  \"w\");\n\tfprintf(fn, \"\%s`\", %s);\n\tfprintf(fn, \"\%s`\", %s);\n\tfprintf(fn, \"\%s`\", %s);\n\tfclose(fn);\n\treturn 0;\n}\n", type, func_name, parameters, type2, tc1, type2, tc2, type2, tc3); // formatting initiation

			write(client, message, sizeof(message));
		}
		else if (s == 3){ // request for solution comparison
			int prob_num;
			read(server, &prob_num, sizeof(prob_num));

			int result; // -1 for not a match
			char message[512];

			printf("Client asking for a solution check...\n");

			int status;
			int f = fork();
			if (!f){
				int pid = getpid();
				char *argv[2];
				argv[0] = "./a.out";
				argv[1] = NULL;
				execvp(argv[0], argv);
			}
			else{
				int pid = wait(&status);
				pid = WEXITSTATUS(status);
				char testc1[50];
				strcpy(testc1, get_testcase1());

				char testc2[50];
				strcpy(testc2, get_testcase2());

				char testc3[50];
				strcpy(testc3, get_testcase3());

				char tests1[50];
				strcpy(tests1, get_ta1(prob_num));

				char tests2[50];
				strcpy(tests2, get_ta2(prob_num));

				char tests3[50];
				strcpy(tests3, get_ta3(prob_num));

				if (!strcmp(testc1, tests1) && !strcmp(testc2, tests2) && !strcmp(testc3, testc3)){
					result = 10;
					printf("Test cases were successful!\n");
				}
				else {
					result = -1;
					printf("Test cases were unsuccessful.\n");
				}
				sprintf(message, "System: %s = %s; You: %s = %s\n", get_tc1(prob_num), tests1, get_tc1(prob_num), testc1);
				sprintf(message + strlen(message), "System: %s = %s; You: %s = %s\n", get_tc2(prob_num), tests2, get_tc2(prob_num), testc2);
				sprintf(message + strlen(message), "System: %s = %s; You: %s = %s\n", get_tc3(prob_num), tests3, get_tc3(prob_num), testc3);
			}
			write(client, &result, sizeof(result));
			write(client, message, sizeof(message));
			remove("a.out");
		}
	}
	return 0;
}
