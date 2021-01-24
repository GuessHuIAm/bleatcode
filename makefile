all: client server

client: client.o problem.o problemset.o csv.o
	gcc -o client client.o problem.o problemset.o csv.o

server: server.o problem.o problemset.o csv.o
	gcc -o server server.o problem.o problemset.o csv.o

client.o: client.c problem.h problemset.h csv.h
	gcc -c client.c

server.o: server.c problem.h problemset.h csv.h
	gcc -c server.c

problem.o: problem.c csv.h
	gcc -c problem.c

problemset.o: problemset.c csv.h
	gcc -c problemset.c

csv.o: csv.h
	gcc -c csv.c

runclient:
	./client

runserver:
	./server

clean:
	rm *.o

clear:
	rm client
	rm server
