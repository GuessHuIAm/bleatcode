#ifndef CSV_H
#define CSV_H

void print_all();
void print_descriptor(int id);
void print_subject(int id);
char * subject(int id);
char * descriptor(int id);

char * get_type(int id);
char * get_func(int id);
char * get_para(int id);
char * get_type2(int id);
char * get_tc1(int id);
char * get_tc2(int id);
char * get_tc3(int id);

char * get_ta1(int id);
char * get_ta2(int id);
char * get_ta3(int id);

int nextPS();

#endif
