#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "csv.h"
#include "problem.h"
#include "problemset.h"

struct problemset *new_set(int ID){
	struct problemset *set = malloc(sizeof(struct problemset));
	
    	int i;
	for (i = 0; i < 20; i++){
		(set->problems)[i] = new_problem(i, 0);
	}
	
	int c;
	char fname[20];
	sprintf(fname, "ps%d.txt", ID);
	FILE* fp = fopen(fname, "w");
	for (i = 0; i < 20; i++){
		struct problem *p = (set->problems)[i];
		c = p->completion;
		fputc(c, fp);
	}
	// Close the file
	fclose(fp);
	return set;
};

struct problemset *retrieve_set(int ID){
	struct problemset *set = malloc(sizeof(struct problemset));
	printf("Getting your problem set... \n");
	char fname[20];
	sprintf(fname, "ps%d.txt", ID);
	FILE* fp = fopen(fname, "r");
        if (!fp){
                printf("Can't open file\n");
		return new_set(nextPS());
	}
	int boolean = 0;
	int i;
	for (i = 0; i < 20; i++){
		fscanf(fp, "%d", &boolean);
		(set->problems)[i] = new_problem(i, boolean);
	}
        // Close the file
        fclose(fp);
	return set;
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
