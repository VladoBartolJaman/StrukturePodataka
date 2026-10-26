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
int insertBefore(Position head, char* surname);

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

int insertBefore(Position head, char* surname) {

	Position newPerson = NULL;

	//PROVJERA PREZIMENA
	pronadiPoPrezimenu(head->next, surname);

	dodajNaKraj(head, "Novi", surname, 2000);
}

int insertAfter(Position head, char* surname) {

	Position newPerson = NULL;

	//PROVJERA PREZIMENA
	pronadiPoPrezimenu(head, surname);

	dodajNaKraj(head, "Novi", surname, 2000);
}

// D) otvori datoteku pa fprintf u nju sve elemente liste, zatim zatvori datoteku

// E) otvori datoteku pa fscanf iz nje sve elemente liste, funkcijom dodajnapocetak/kraj ubaci u listu, zatim zatvori datoteku

int sortfun(Position head, ) {

	Position p = head->next;
	Position q = head;
	Position temp = NULL;

	while(p->next != NULL){
	if(strcmp(p->surname, p->next->surname) > 0) {

		temp = p->next;
		q->next = temp;
		p->next = temp->next;
		temp->next = p;
		q = head;
		p = q->next;
	}
	else {
		q = p; 
		p = p->next;
	}
}

