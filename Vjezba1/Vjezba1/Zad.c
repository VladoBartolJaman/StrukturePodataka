#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

typedef struct student
{
	char name[50];
	char surname[50];
	int points;

}stud;

int counter(const char* dat) {

	FILE* f = fopen(dat, "r");

	if (f == NULL) {
		perror("ERROR");

		return -1;
	}

	int counter = 0;

	char symbol;

	symbol = fgetc(f);
	while (symbol != EOF) {
		symbol = fgetc(f);
		if (symbol == "\n")
			counter++;
	}
	fclose(f);

	return counter;
}
int main()
{
	printf("Unesite ime datoteke: ");
}