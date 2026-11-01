#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


struct _Clan;
typedef struct _Clan* Position;
typedef struct _Clan
{
	int koeficijent;
	int eksponent;
	Position next;
} Clan;

Position kreirajClan(int koef, int eksp);
int dodajSortirano(Position head, int koef, int eksp);
int ispisiPolinom(Position first);
int citajPolinomIzDatoteke(Position head, const char* filename);
int zbrojiPolinome(Position headA, Position headB, Position headRez);
int pomnoziPolinome(Position headA, Position headB, Position headRez);
int oslobodiListu(Position head);

int main()
{
	Clan headA = { 0, 0, NULL };
	Clan headB = { 0, 0, NULL };
	Clan headZbroj = { 0, 0, NULL };
	Clan headUmnozak = { 0, 0, NULL };

	// Citanje polinoma iz datoteka
	printf("Citanje polinoma A iz datoteke polinom1.txt");
	if (citajPolinomIzDatoteke(&headA, "polinom1.txt") != 0)
	{
		printf("Greska pri citanju polinoma A!\n");
		return -1;
	}
	printf("Polinom A: ");
	ispisiPolinom(headA.next);

	printf("\nCitanje polinoma B iz datoteke polinom2.txt");
	if (citajPolinomIzDatoteke(&headB, "polinom2.txt") != 0)
	{
		printf("Greska pri citanju polinoma B!\n");
		oslobodiListu(&headA);
		return -1;
	}
	printf("Polinom B: ");
	ispisiPolinom(headB.next);

	// Zbrajanje polinoma
	printf("\nZBRAJANJE");
	zbrojiPolinome(&headA, &headB, &headZbroj);
	printf("A + B = ");
	ispisiPolinom(headZbroj.next);

	// Mnozenje polinoma
	printf("\nMNOZENJE");
	pomnoziPolinome(&headA, &headB, &headUmnozak);
	printf("A * B = ");
	ispisiPolinom(headUmnozak.next);

	printf("\n");

	// Oslobadanje memorije
	oslobodiListu(&headA);
	oslobodiListu(&headB);
	oslobodiListu(&headZbroj);
	oslobodiListu(&headUmnozak);

	return 0;
}

// Kreira novi clan polinoma
Position kreirajClan(int koef, int eksp)
{
	Position newClan = (Position)malloc(sizeof(Clan));
	if (newClan == NULL)
	{
		perror("ERROR alokacije");
		return NULL;
	}

	newClan->koeficijent = koef;
	newClan->eksponent = eksp;
	newClan->next = NULL;

	return newClan;
}

// Dodaje clan sortirano po eksponentu (silazno)
// Ako clan s istim eksponentom vec postoji, zbraja koeficijente
int dodajSortirano(Position head, int koef, int eksp)
{
	if (koef == 0)
	{
		return 0;
	}

	Position prev = head;
	Position temp = head->next;

	// Trazi pravu poziciju (silazni redoslijed eksponenata)
	while (temp != NULL && temp->eksponent > eksp)
	{
		prev = temp;
		temp = temp->next;
	}

	// Ako clan s istim eksponentom vec postoji, zbroji koeficijente
	if (temp != NULL && temp->eksponent == eksp)
	{
		temp->koeficijent += koef;
		// Ako je koeficijent postao 0, obrisi clan
		if (temp->koeficijent == 0)
		{
			prev->next = temp->next;
			free(temp);
		}
		return 0;
	}

	// Inace, kreiraj novi clan i umetni ga
	Position newClan = kreirajClan(koef, eksp);
	if (newClan == NULL)
	{
		return -1;
	}

	newClan->next = temp;
	prev->next = newClan;

	return 0;
}

// Ispisuje polinom u citljivom obliku
int ispisiPolinom(Position first)
{
	Position temp = first;

	if (temp == NULL)
	{
		printf("0");
		return 0;
	}

	int isFirst = 1;
	while (temp != NULL)
	{
		int koef = temp->koeficijent;
		int eksp = temp->eksponent;

		if (!isFirst)
		{
			if (koef > 0)
				printf(" + ");
			else
			{
				printf(" - ");
				koef = -koef;
			}
		}
		else
		{
			if (koef < 0)
			{
				printf("-");
				koef = -koef;
			}
		}

		if (eksp == 0)
		{
			printf("%d", koef);
		}
		else if (eksp == 1)
		{
			if (koef == 1)
				printf("x");
			else
				printf("%dx", koef);
		}
		else
		{
			if (koef == 1)
				printf("x^%d", eksp);
			else
				printf("%dx^%d", koef, eksp);
		}

		isFirst = 0;
		temp = temp->next;
	}

	return 0;
}

// Cita koeficijente i eksponente iz datoteke
// Format datoteke: svaki redak sadrzi "koeficijent eksponent"
int citajPolinomIzDatoteke(Position head, const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		perror("ERROR otvaranja datoteke za citanje");
		return -1;
	}

	int koef, eksp;
	while (fscanf(fp, "%d %d", &koef, &eksp) == 2)
	{
		dodajSortirano(head, koef, eksp);
	}

	fclose(fp);
	printf("Polinom uspjesno ucitan iz datoteke \"%s\".\n", filename);
	return 0;
}

// Zbraja dva polinoma (A + B) i rezultat sprema u headRez
int zbrojiPolinome(Position headA, Position headB, Position headRez)
{
	Position tempA = headA->next;
	Position tempB = headB->next;

	// Dodaj sve clanove iz polinoma A
	while (tempA != NULL)
	{
		dodajSortirano(headRez, tempA->koeficijent, tempA->eksponent);
		tempA = tempA->next;
	}

	// Dodaj sve clanove iz polinoma B
	while (tempB != NULL)
	{
		dodajSortirano(headRez, tempB->koeficijent, tempB->eksponent);
		tempB = tempB->next;
	}

	return 0;
}

// Mnozi dva polinoma (A * B) i rezultat sprema u headRez
int pomnoziPolinome(Position headA, Position headB, Position headRez)
{
	Position tempA = headA->next;

	while (tempA != NULL)
	{
		Position tempB = headB->next;
		while (tempB != NULL)
		{
			int noviKoef = tempA->koeficijent * tempB->koeficijent;
			int noviEksp = tempA->eksponent + tempB->eksponent;
			dodajSortirano(headRez, noviKoef, noviEksp);
			tempB = tempB->next;
		}
		tempA = tempA->next;
	}

	return 0;
}

// Oslobada sve dinamicki alocirane clanove liste
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

