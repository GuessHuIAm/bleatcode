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
	printf("Problem %d", num);
	printf("\t%s", subject(num));
	printf(" - %s", get_func(num));
	printf("\t  Completion Status: %c\n", c);
	return;
}
