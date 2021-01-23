#ifndef PROBLEM_H
#define PROBLEM_H

struct problem {
	int id;
	char subject[100];
	int completion;
}

struct problem *new_problem(int num);
void problem *solve(int num);
void print_subject(int num);
void print_descriptor(int num);

#endif
