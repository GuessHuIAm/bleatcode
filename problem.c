#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "problem.h"
#include "csv.h"

struct problem *new_problem(int num){
	struct problem *np;
	np = malloc(sizeof(struct problem));
	np->id = num;
	np->completion = 0;
	return np;
}

void print_problem(struct problem *p){
	char c;
	if (p->completion)
		c = '+';
	else
		c = '-';
	printf("Problem %d\t%s\t     Completion Status: %c\n", p->id, subject(p->id), c);
	return;
}
