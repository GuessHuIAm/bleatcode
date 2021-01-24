all: client server

client: client.o problem.o problem_set.o csv.o
	gcc -o client client.o problem.o problem_set.o csv.o

server: server.o problem.o problem_set.o csv.o
	gcc -o server server.o problem.o problem_set.o csv.o

client.o: client.c problem.h problem_set.h csv.h
	gcc -c client.c

server.o: server.c problem.h problem_set.h csv.h
	gcc -c server.c

problem.o: problem.c csv.h
	gcc -c problem.c

problem_set.o: problem_set.c csv.h
	gcc -c problem.c

runclient:
	./client

runserver:
	./server

clean:
	rm *.o

clear:
	rm client
	rm server
