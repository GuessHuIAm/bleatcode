#ifndef PROBLEM_SET_H
#define PROBLEM_SET_H

struct problemset {
	struct problem * problems[21];
}

struct problemset *new_set();
void print_set(struct problemset *ps);

#endif
