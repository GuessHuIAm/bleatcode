#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

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

    		write(client, "Howdy!", sizeof("Howdy!"));
		printf("Acknowledgement <Howdy!> sent\n");

		//server reads from client
    		char message[32];
    		read(server, message, sizeof(message));
    		printf("Acknowledgement from client received <%s>\n", message);

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
