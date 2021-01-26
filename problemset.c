#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "csv.h"
#include "problem.h"
#include "problemset.h"

struct problemset *new_set(){
	struct problemset *set = malloc(sizeof(struct problemset));
    	int i;
	for (i = 0; i < 20; i++)
		(set->problems)[i] = new_problem(i);
	return set;
};

struct problemset *retrieve_set(int ID){
	struct problemset *set = malloc(sizeof(struct problemset));
	
	return set
}

void print_set(char *name, struct problemset *ps){
	if (ps == NULL){
		printf("Problem set is NULL\n");
		return;
	}
	printf("%s's Problem Set!\n", name);

	int i;
	struct problem *p;
	for (i = 0; i < 20; i++){
        	struct problem *p = ps->problems[i];
        	print_problem(p);
	}
	sleep(1);
	return;
};

void solve(struct problemset *ps, int id){
	struct problem *p = ps->problems[id];
	p->completion = 1;
	return;
};
