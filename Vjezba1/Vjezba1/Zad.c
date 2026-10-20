#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
#define MAX_BODOVA 100

typedef struct student
{
	char name[50];
	char surname[50];
	int points;
} stud;

int counter(const char* dat) {
	FILE* f = fopen(dat, "r");
	if (f == NULL) {
		perror("ERROR");
		return -1;
	}

	int counter = 0;
	int symbol;

	while ((symbol = fgetc(f)) != EOF) {
		if (symbol == '\n')
			counter++;
	}
	fclose(f);

	return counter;
}

stud* alocirajIUcitaj(int brojStudenata, const char* dat) {
	FILE* f = fopen(dat, "r");
	if (f == NULL) 
	{
		perror("ERROR pri otvaranju datoteke");
		return NULL;
	}

	stud* studenti = (stud*)malloc(brojStudenata * sizeof(stud));
	if (studenti == NULL)
	{
		perror("ERROR pri alokaciji memorije");
		fclose(f);
		return NULL;
	}

	for (int i = 0; i < brojStudenata; i++)
	{
		fscanf(f, "%s %s %d", studenti[i].name, studenti[i].surname, &studenti[i].points);
	}

	fclose(f);
	return studenti;
}

int main()
{
	char fileName[MAX];
	printf("Unesite ime datoteke: ");
	if (scanf("%s", fileName) != 1) 
	{
		return -1;
	}

	int brojStudenata = counter(fileName);
	if (brojStudenata <= 0) 
	{
		printf("Datoteka je prazna ili ne postoji.\n");
		return -1;
	}

	printf("Broj studenata u datoteci: %d\n", brojStudenata);

	stud* studenti = alocirajIUcitaj(brojStudenata, fileName);
	if (studenti == NULL) {
		return -1;
	}

	for (int i = 0; i < brojStudenata; i++) 
	{
		double rel_bodovi = ((double)studenti[i].points / MAX_BODOVA) * 100.0;
		printf("%s %s %d %.2lf\n", studenti[i].name,studenti[i].surname,studenti[i].points,rel_bodovi);
	}

	free(studenti);
	return 0;
}