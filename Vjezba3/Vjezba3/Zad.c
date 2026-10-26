#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 50

struct _Person;
typedef struct _Person* Position;
typedef struct _Person
{
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
} Person;

typedef Person Osoba;
typedef Position Pozicija;

Position kreirajOsobu(const char* name, const char* surname, int birthYear);
int dodajNaPocetak(Position head, const char* name, const char* surname, int birthYear);
int ispisiListu(Position first);
int dodajNaKraj(Position head, const char* name, const char* surname, int birthYear);
Position pronadiPoPrezimenu(Position first, const char* surname);
Position pronadiPrethodni(Position head, const char* surname);
int obrisiElement(Position head, const char* surname);
int oslobodiListu(Position head);
int dodajIza(Position head, const char* surname, const char* newName, const char* newSurname, int newYear);
int dodajIspred(Position head, const char* surname, const char* newName, const char* newSurname, int newYear);
int sortirajListu(Position head);
int zapisiUDatoteku(Position head, const char* filename);
int citajIzDatoteke(Position head, const char* filename);

int main()
{
	Person head = { "", "", 0, NULL };
	Position pronadena = NULL;

	// A. Dinamicki dodaje novi element na pocetak liste
	printf("Dodavanje elemenata na pocetak liste\n");
	dodajNaPocetak(&head, "Ana", "Anic", 1998);
	dodajNaPocetak(&head, "Ivo", "Ivic", 1995);
	printf("Dodani su 'Ana Anic (1998)' i 'Ivo Ivic (1995)'.\n");

	// B. Ispisuje listu
	printf("\nIspis trenutne liste\n");
	ispisiListu(head.next);

	// C. Dinamicki dodaje novi element na kraj liste
	printf("\nDodavanje elemenata na kraj liste\n");
	dodajNaKraj(&head, "Marko", "Maric", 2000);
	dodajNaKraj(&head, "Lucija", "Lukic", 2002);
	printf("Dodani su 'Marko Maric (2000)' i 'Lucija Lukic (2002)'.\n");
	ispisiListu(head.next);

	// D. Pronalazi element u listi (po prezimenu) - trazi ima li osobe ili nema
	printf("\nPretraga po prezimenu (provjera ima li osobe ili nema)\n");

	pronadena = pronadiPoPrezimenu(head.next, "Maric");
	if (pronadena != NULL)
	{
		printf("Osoba s prezimenom \"Maric\" postoji u listi.\n");
	}
	else
	{
		printf("Osoba s prezimenom \"Maric\" ne postoji u listi.\n");
	}

	pronadena = pronadiPoPrezimenu(head.next, "Horvat");
	if (pronadena != NULL)
	{
		printf("Osoba s prezimenom \"Horvat\" postoji u listi.\n");
	}
	else
	{
		printf("Osoba s prezimenom \"Horvat\" ne postoji u listi.\n");
	}

	// E. Brise odredeni element iz liste
	printf("\nBrisanje odredenog elementa iz liste\n");
	printf("Brisanje osobe s prezimenom \"Ivic\":\n");
	obrisiElement(&head, "Ivic");
	ispisiListu(head.next);

	printf("\nPokusaj brisanja nepostojece osobe (\"Horvat\"):\n");
	obrisiElement(&head, "Horvat");

	// ============ ZADATAK 3 ============

	// A. Dinamicki dodaje novi element iza odredenog elementa
	printf("\n--- Zadatak 3A: Dodavanje iza odredenog elementa ---\n");
	printf("Dodavanje 'Pero Peric (1990)' iza osobe s prezimenom \"Anic\":\n");
	dodajIza(&head, "Anic", "Pero", "Peric", 1990);
	ispisiListu(head.next);

	// B. Dinamicki dodaje novi element ispred odredenog elementa
	printf("\n--- Zadatak 3B: Dodavanje ispred odredenog elementa ---\n");
	printf("Dodavanje 'Maja Majic (1997)' ispred osobe s prezimenom \"Maric\":\n");
	dodajIspred(&head, "Maric", "Maja", "Majic", 1997);
	ispisiListu(head.next);

	// C. Sortira listu po prezimenima osoba
	printf("\n--- Zadatak 3C: Sortiranje liste po prezimenu ---\n");
	sortirajListu(&head);
	printf("Lista nakon sortiranja:\n");
	ispisiListu(head.next);

	// D. Upisuje listu u datoteku
	printf("\n--- Zadatak 3D: Upis liste u datoteku ---\n");
	zapisiUDatoteku(&head, "lista.txt");

	// E. Cita listu iz datoteke
	printf("\n--- Zadatak 3E: Citanje liste iz datoteke ---\n");
	oslobodiListu(&head);
	printf("Lista obrisana. Citanje iz datoteke...\n");
	citajIzDatoteke(&head, "lista.txt");
	printf("Lista ucitana iz datoteke:\n");
	ispisiListu(head.next);

	// Oslobadanje dinamicki alocirane memorije na kraju
	oslobodiListu(&head);

	return 0;
}

Position kreirajOsobu(const char* name, const char* surname, int birthYear)
{
	Position newPerson = (Position)malloc(sizeof(Person));
	if (newPerson == NULL)
	{
		perror("ERROR alokacije");
		return NULL;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}

int dodajNaPocetak(Position head, const char* name, const char* surname, int birthYear)
{
	Position newPerson = kreirajOsobu(name, surname, birthYear);
	if (newPerson == NULL)
	{
		return -1;
	}

	newPerson->next = head->next;
	head->next = newPerson;

	return 0;
}

int ispisiListu(Position first)
{
	Position temp = first;

	if (temp == NULL)
	{
		printf("Lista je prazna.\n");
		return 0;
	}

	printf("\n%s %s %s\n", "Ime", "Prezime", "Godina");
	while (temp != NULL)
	{
		printf("%s %s %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	return 0;
}

int dodajNaKraj(Position head, const char* name, const char* surname, int birthYear)
{
	Position newPerson = kreirajOsobu(name, surname, birthYear);
	if (newPerson == NULL)
	{
		return -1;
	}

	Position temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	temp->next = newPerson;

	return 0;
}

Position pronadiPoPrezimenu(Position first, const char* surname)
{
	Position temp = first;

	while (temp != NULL)
	{
		if (strcmp(temp->surname, surname) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}

	return NULL;
}

Position pronadiPrethodni(Position head, const char* surname)
{
	Position temp = head;

	while (temp->next != NULL && strcmp(temp->next->surname, surname) != 0)
	{
		temp = temp->next;
	}

	if (temp->next == NULL)
	{
		return NULL;
	}

	return temp;
}

int obrisiElement(Position head, const char* surname)
{
	Position prev = pronadiPrethodni(head, surname);

	if (prev == NULL)
	{
		printf("Osoba s prezimenom \"%s\" nije pronadena u listi.\n", surname);
		return -1;
	}

	Position toDelete = prev->next;
	prev->next = toDelete->next;
	free(toDelete);

	printf("Osoba s prezimenom \"%s\" je uspjesno obrisana.\n", surname);
	return 0;
}

int oslobodiListu(Position head)
{
	Position temp = head->next;

	while (temp != NULL)
	{
		Position toDelete = temp;
		temp = temp->next;
		free(toDelete);
	}

	head->next = NULL;
	return 0;
}

//ZADATAK 3

// A. Dinamicki dodaje novi element iza odredenog elementa (po prezimenu)
int dodajIza(Position head, const char* surname, const char* newName, const char* newSurname, int newYear)
{
	Position pronadena = pronadiPoPrezimenu(head->next, surname);
	if (pronadena == NULL)
	{
		printf("Osoba s prezimenom \"%s\" nije pronadena.\n", surname);
		return -1;
	}

	Position newPerson = kreirajOsobu(newName, newSurname, newYear);
	if (newPerson == NULL)
	{
		return -1;
	}

	newPerson->next = pronadena->next;
	pronadena->next = newPerson;

	printf("Osoba '%s %s (%d)' dodana iza osobe s prezimenom \"%s\".\n", newName, newSurname, newYear, surname);
	return 0;
}

// B. Dinamicki dodaje novi element ispred odredenog elementa (po prezimenu)
int dodajIspred(Position head, const char* surname, const char* newName, const char* newSurname, int newYear)
{
	Position prev = pronadiPrethodni(head, surname);
	if (prev == NULL)
	{
		printf("Osoba s prezimenom \"%s\" nije pronadena.\n", surname);
		return -1;
	}

	Position newPerson = kreirajOsobu(newName, newSurname, newYear);
	if (newPerson == NULL)
	{
		return -1;
	}

	newPerson->next = prev->next;
	prev->next = newPerson;

	printf("Osoba '%s %s (%d)' dodana ispred osobe s prezimenom \"%s\".\n", newName, newSurname, newYear, surname);
	return 0;
}

// C. Sortira listu po prezimenima osoba (bubble sort zamjenom pokazivaca)
int sortirajListu(Position head)
{
	Position p = head->next;
	Position q = head;
	Position temp = NULL;

	if (p == NULL)
	{
		return 0;
	}

	while (p->next != NULL)
	{
		if (strcmp(p->surname, p->next->surname) > 0)
		{
			temp = p->next;
			q->next = temp;
			p->next = temp->next;
			temp->next = p;
			q = head;
			p = q->next;
		}
		else
		{
			q = p;
			p = p->next;
		}
	}

	return 0;
}

// D. Upisuje listu u datoteku
int zapisiUDatoteku(Position head, const char* filename)
{
	FILE* fp = fopen(filename, "w");
	if (fp == NULL)
	{
		perror("ERROR otvaranja datoteke za pisanje");
		return -1;
	}

	Position temp = head->next;
	while (temp != NULL)
	{
		fprintf(fp, "%s %s %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	fclose(fp);
	printf("Lista uspjesno zapisana u datoteku \"%s\".\n", filename);
	return 0;
}

// E. Cita listu iz datoteke
int citajIzDatoteke(Position head, const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		perror("ERROR otvaranja datoteke za citanje");
		return -1;
	}

	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;

	while (fscanf(fp, "%s %s %d", name, surname, &birthYear) == 3)
	{
		dodajNaKraj(head, name, surname, birthYear);
	}

	fclose(fp);
	printf("Lista uspjesno ucitana iz datoteke \"%s\".\n", filename);
	return 0;
}

