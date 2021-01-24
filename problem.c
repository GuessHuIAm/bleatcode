#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct problem *new_problem(int num){
	struct problem *np;
	np = malloc(sizeof(struct problem));
	np->id = num;
	np->completion = 0;
	return np;
}

void *solve(int num){
	p->completion = 1;
}
