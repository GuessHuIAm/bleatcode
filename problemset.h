#ifndef PROBLEM_SET_H
#define PROBLEM_SET_H

struct problemset {
	struct problem * problems[21];
};

struct problemset *new_set(int id);
struct problemset *retrieve_set(int id);
void print_set(char *name, struct problemset *ps);
void solve(struct problemset *ps, int id);

#endif
