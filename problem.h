#ifndef PROBLEM_H
#define PROBLEM_H

struct problem {
	int id;
	char subject[100];
	int completion;
};

struct problem *new_problem(int num, int boolean);
void print_problem(struct problem *);

#endif
