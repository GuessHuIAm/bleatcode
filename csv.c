#include <stdio.h>
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
                printf("Can't open file\n");                                                                                                    else {
        char buffer[1024];
        int row = 0;
        int column = 0;
        while (fgets(buffer, 1024, fp)) {
		if (row == id){
                	// Turning the ` into new lines
                        while (strchr(buffer, '`') != NULL){
                               	*strchr(buffer, '`') = '\n';
                       	}
                       	// Splitting the data
                       	char* value = strtok(buffer, ";");
                       	while (value) {
                               	if (column == 2){
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

char * subject(int id){
        FILE* fp = fopen("the_problems.csv", "r");
        if (!fp)
                printf("Can't open file\n");
	char buffer[1024];
       	int row = 0;
        int column = 0;
        while (fgets(buffer, 1024, fp)) {
		if (row == id){
                	// Turning the ` into new lines
                	while (strchr(buffer, '`') != NULL){
				*strchr(buffer, '`') = '\n';
 			}
			// Splitting the data
			char* value = strtok(buffer, ";");
			while (value) {
 				if (column == 1){
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

char * descriptor(int id){
        FILE* fp = fopen("the_problems.csv", "r");
        if (!fp)
                printf("Can't open file\n");
	char buffer[1024];
       	int row = 0;
        int column = 0;
        while (fgets(buffer, 1024, fp)) {
		if (row == id){
                	// Turning the ` into new lines
                	while (strchr(buffer, '`') != NULL){
				*strchr(buffer, '`') = '\n';
 			}
			// Splitting the data
			char* value = strtok(buffer, ";");
			while (value) {
 				if (column == 2){
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
        return "Can't find it\n";
}

int nextPS(){
	int i = 0;
	char fname[20];
	sprintf(fname, "ps%d.csv", i);
	while (access(fname, F_OK) == 0) { // file exists
		i++;
		sprintf(fname, "ps%d.csv", i);
	}
	// file doesn't exist
	return i;
}
