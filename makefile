all: client server

client: client.c
	gcc -o client client.c

server: server.c
	gcc -o server server.c

runclient:
	./client

runserver:
	./server

clien:
	rm client
	rm server
