#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "problem.h"
#include "csv.h"

struct problem *new_problem(int num, int boolean){
	struct problem *np;
	np = malloc(sizeof(struct problem));
	np->id = num;
	np->completion = boolean;
	return np;
}

void print_problem(struct problem *p){
	char c;
	int num = p->id;
	if (p->completion)
		c = '+';
	else
		c = '-';
	printf("Problem %d\t %s / %s\t  Completion Status: %c\n", num, subject(num), get_func(num), c);
	return;
}
