#ifndef PROBLEM_SET_H
#define PROBLEM_SET_H

struct problemset {
	struct problem * problems[21];
};

struct problemset *new_set();
struct problemset *retrieveset(int id);
void print_set(char *name, struct problemset *ps);
void solve(struct problemset *ps, int id);

#endif
