#ifndef CSV_H
#define CSV_H

void print_all();
void print_descriptor(int id);
void print_subject(int id);

char * helper1(int id, int col);
char * subject(int id);
char * get_func(int id);
char * descriptor(int id);

char * helper2(int id, int col);
char * get_type(int id);
char * get_para(int id);
char * get_type2(int id);
char * get_tc1(int id);
char * get_tc2(int id);
char * get_tc3(int id);

char * helper3(int id, int col);
char * get_ta1(int id);
char * get_ta2(int id);
char * get_ta3(int id);
char * get_solution(int id);

int nextPS();

#endif
