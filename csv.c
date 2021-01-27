#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_all(){
	FILE* fp = fopen("the_problems.csv", "r");
	if (!fp)
		printf("Can't open file\n");
	else {
		char buffer[1024];
		int row = 0;
		int column = 0;
		while (fgets(buffer, 1024, fp)) {
			column = 0;
			buffer[strcspn(buffer, "\n")] = '\0';
			// Turning the ` into new lines
			while (strchr(buffer, '`') != NULL){
				*strchr(buffer, '`') = '\n';
			}
			// Splitting the data
			char* value = strtok(buffer, ";");
			while (value) {
				if (column == 1){
					printf(" - ");
                		}
                		// Column 3
				if (column == 2){
					printf("\nDescription: ");
				}
                		printf("%s", value);
                		value = strtok(NULL, ";");
                		column++;
			}
			printf("\n");
			row++;
		}
        // Close the file
        fclose(fp);
	}
	return;
}

void print_descriptor(int id){
	FILE* fp = fopen("the_problems.csv", "r");
        if (!fp)
                printf("Can't open file\n");
	else {
		char buffer[1024];
		int row = 0;
		int column = 0;
		while (fgets(buffer, 1024, fp)) {
			if (row == id){
				buffer[strcspn(buffer, "\n")] = '\0';
				// Turning the ` into new lines
				while (strchr(buffer, '`') != NULL){
					*strchr(buffer, '`') = '\n';
				}
				// Splitting the data
				char* value = strtok(buffer, ";");
				while (value) {
					if (column == 3){
						printf("%s", value);
					}
					value = strtok(NULL, ";");
					column++;
				}
			}
			row++;
		}
        // Close the file
        fclose(fp);
	}
        return;
}

void print_subject(int id){
        FILE* fp = fopen("the_problems.csv", "r");
        if (!fp)
                printf("Can't open file\n");
	char buffer[1024];
       	int row = 0;
        int column = 0;
        while (fgets(buffer, 1024, fp)) {
		if (row == id){
			buffer[strcspn(buffer, "\n")] = '\0';
                	// Turning the ` into new lines
                	while (strchr(buffer, '`') != NULL){
				*strchr(buffer, '`') = '\n';
 			}
			// Splitting the data
			char* value = strtok(buffer, ";");
			while (value) {
 				if (column == 1)
					printf("%s", value);
				value = strtok(NULL, ";");
				column++;
			}
		}
		row++;
        }
        // Close the file
        fclose(fp);
        return;
}

char * helper1(int id, int col){ // col = 1->SUBJECT 2->FUNCTIONNAME 3->DESCRIPTOR
	FILE* fp = fopen("the_problems.csv", "r");
        if (!fp)
                printf("Can't open file\n");
	char buffer[1024];
       	int row = 0;
        int column = 0;
        while (fgets(buffer, 1024, fp)) {
		if (row == id){
			buffer[strcspn(buffer, "\n")] = '\0';
                	// Turning the ` into new lines
                	while (strchr(buffer, '`') != NULL){
				*strchr(buffer, '`') = '\n';
 			}
			// Splitting the data
			char* value = strtok(buffer, ";");
			while (value) {
 				if (column == col){
					fclose(fp);
					return value;
				}
				value = strtok(NULL, ";");
				column++;
			}
		}
		row++;
        }
        fclose(fp);
        return "Can't find it";
}

char * subject(int id){
	//printf("subject() == %s", helper1(id, 1, 32));
	return helper1(id, 1);
}

char * get_func(int id){
	//printf("get_func() == %s", helper1(id, 2, 32));
	return helper1(id, 2);
}

char * descriptor(int id){
	//printf("descriptor() == %s", helper1(id, 3, 32));
	return helper1(id, 3);
}

char * helper2(int id, int col){ // col = 1->RETURNVALUE 2->PARAMETERS 3->%RETURNVALUE 4->TESTCASE1 5->TESTCASE2 6->TESTCASE3
	FILE* fp = fopen("the_extra_info.csv", "r");
        if (!fp)
                printf("Can't open file\n");
	char buffer[1024];
       	int row = 0;
        int column = 0;
        while (fgets(buffer, 1024, fp)) {
		if (row == id){
			buffer[strcspn(buffer, "\n")] = '\0';
                	// Turning the ` into new lines
                	while (strchr(buffer, '`') != NULL){
				*strchr(buffer, '`') = '\n';
 			}
			// Splitting the data
			char* value = strtok(buffer, ";");
			while (value) {
 				if (column == col){
					fclose(fp);
					return value;
				}
				value = strtok(NULL, ";");
				column++;
			}
		}
		row++;
        }
        fclose(fp);
        return "Can't find it";
}

char * get_type(int id){
	return helper2(id, 1);
}
char * get_para(int id){
	return helper2(id, 2);
}
char * get_type2(int id){
	return helper2(id, 3);
}
char * get_tc1(int id){
	return helper2(id, 4);
}
char * get_tc2(int id){
	return helper2(id, 5);
}
char * get_tc3(int id){
	return helper2(id, 6);
}

char * helper3(int id, int col){ // col = 1->SOLUTION1 2->SOLUTION2 3->SOLUTION3
	FILE* fp = fopen("the_solutions.csv", "r");
        if (!fp)
                printf("Can't open file\n");
	char buffer[1024];
       	int row = 0;
        int column = 0;
        while (fgets(buffer, 1024, fp)) {
		if (row == id){
			buffer[strcspn(buffer, "\n")] = '\0';
                	// Turning the ` into new lines
                	while (strchr(buffer, '`') != NULL){
				*strchr(buffer, '`') = '\n';
 			}
			// Splitting the data
			char* value = strtok(buffer, "~");
			while (value) {
 				if (column == col){
					fclose(fp);
					return value;
				}
				value = strtok(NULL, "~");
				column++;
			}
		}
		row++;
        }
        fclose(fp);
        return "Can't find it";
}

char * get_ta1(int id){
	return helper3(id, 1);
}
char * get_ta2(int id){
	return helper3(id, 2);
}
char * get_ta3(int id){
	return helper3(id, 3);
}
char * get_solution(int id){
	return helper3(id, 4);
}

char * helper4(int r){ // col = 1->SOLUTION1 2->SOLUTION2 3->SOLUTION3
        FILE *f = fopen("solution.txt", "r");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

	char *string = malloc(fsize + 1);
	fread(string, 1, fsize, f);
	fclose(f);

	string[fsize] = 0;
	char buffer[1028];

	strcpy(buffer, string);
	free(string);
	remove("solution.txt");

	printf("buffer: %s\n", buffer);

	int row = 1;
	// Splitting the data
	char* value = strtok(buffer, "`");
	while (value) {
 		if (row == r){
			printf("value = %s\n", value);
			return value;
		}
		value = strtok(NULL, "`");
		row++;
	}
        return "Can't find it";
}

char * get_testcase1(){
	return helper4(1);
}

char * get_testcase2(){
	return helper4(2);
}

char * get_testcase3(){
	return helper4(3);
}

int nextPS(){
	int i = 0;
	char fname[20];
	sprintf(fname, "ps%d.txt", i);
	while (access(fname, F_OK) == 0) { // if file exists, keep updating i
		i++;
		sprintf(fname, "ps%d.txt", i);
	}
	// file doesn't exist
	return i;
}
