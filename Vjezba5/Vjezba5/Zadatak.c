#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 256



struct _StackNode;
typedef struct _StackNode* Position;
typedef struct _StackNode
{
	double data;
	Position next;
} StackNode;

Position kreirajCvor(double value);
int push(Position top, double value);
double pop(Position top);
double peek(Position top);
int isEmpty(Position top);
int oslobodiStog(Position top);
int izracunajPostfiks(const char* filename);

int main()
{
	char fileName[MAX];
	printf("Unesite ime datoteke s postfiks izrazom: ");
	if (scanf("%s", fileName) != 1)
	{
		printf("Greska pri unosu imena datoteke\n");
		return -1;
	}

	izracunajPostfiks(fileName);

	return 0;
}

// Kreira novi cvor stoga
Position kreirajCvor(double value)
{
	Position newNode = (Position)malloc(sizeof(StackNode));
	if (newNode == NULL)
	{
		perror("ERROR alokacije");
		return NULL;
	}

	newNode->data = value;
	newNode->next = NULL;

	return newNode;
}

// Stavlja element na vrh stoga
int push(Position top, double value)
{
	Position newNode = kreirajCvor(value);
	if (newNode == NULL)
	{
		return -1;
	}

	newNode->next = top->next;
	top->next = newNode;

	return 0;
}

// Skida element s vrha stoga i vraca njegovu vrijednost
double pop(Position top)
{
	if (isEmpty(top))
	{
		printf("Greska: Stog je prazan\n");
		return 0;
	}

	Position toDelete = top->next;
	double value = toDelete->data;
	top->next = toDelete->next;
	free(toDelete);

	return value;
}

// Vraca vrijednost elementa na vrhu stoga bez skidanja
double peek(Position top)
{
	if (isEmpty(top))
	{
		printf("Greska: Stog je prazan");
		return 0;
	}

	return top->next->data;
}

// Provjerava je li stog prazan
int isEmpty(Position top)
{
	return (top->next == NULL);
}

// Oslobada cijeli stog
int oslobodiStog(Position top)
{
	Position temp = top->next;

	while (temp != NULL)
	{
		Position toDelete = temp;
		temp = temp->next;
		free(toDelete);
	}

	top->next = NULL;
	return 0;
}

// Cita postfiks izraz iz datoteke i racuna rezultat koristeci stog
int izracunajPostfiks(const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		perror("ERROR otvaranja datoteke");
		return -1;
	}

	StackNode top = { 0, NULL };
	char token[MAX];
	double operand1, operand2, rezultat;

	printf("Citanje postfiks izraza iz datoteke %s\n", filename);

	while (fscanf(fp, "%s", token) == 1)
	{
		// Ako je token broj (ili negativan broj)
		if (isdigit(token[0]) || (token[0] == '-' && strlen(token) > 1 && isdigit(token[1])))
		{
			double value = atof(token);
			push(&top, value);
			printf("Push: %.2lf\n", value);
		}
		// Ako je token operator
		else if (strlen(token) == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/'))
		{
			if (isEmpty(&top))
			{
				printf("Greska: Nedovoljno operanada za operator '%s'!\n", token);
				fclose(fp);
				oslobodiStog(&top);
				return -1;
			}
			operand2 = pop(&top);

			if (isEmpty(&top))
			{
				printf("Greska: Nedovoljno operanada za operator '%s'!\n", token);
				fclose(fp);
				oslobodiStog(&top);
				return -1;
			}
			operand1 = pop(&top);

			switch (token[0])
			{
			case '+':
				rezultat = operand1 + operand2;
				break;
			case '-':
				rezultat = operand1 - operand2;
				break;
			case '*':
				rezultat = operand1 * operand2;
				break;
			case '/':
				if (operand2 == 0)
				{
					printf("Greska: Dijeljenje s nulom!\n");
					fclose(fp);
					oslobodiStog(&top);
					return -1;
				}
				rezultat = operand1 / operand2;
				break;
			}

			printf("Pop: %.2lf, Pop: %.2lf => %.2lf %c %.2lf = %.2lf\n",operand1, operand2, operand1, token[0], operand2, rezultat);

			push(&top, rezultat);
			printf("Push: %.2lf\n", rezultat);
		}
		else
		{
			printf("Greska: Nepoznat token '%s'!\n", token);
			fclose(fp);
			oslobodiStog(&top);
			return -1;
		}
	}

	fclose(fp);

	if (isEmpty(&top))
	{
		printf("\nGreska: Stog je prazan nakon obrade!\n");
		oslobodiStog(&top);
		return -1;
	}

	rezultat = pop(&top);

	if (!isEmpty(&top))
	{
		printf("\nGreska: Na stogu je ostalo vise od jednog elementa\n");
		oslobodiStog(&top);
		return -1;
	}

	printf("Rezultat postfiks izraza: %.2lf\n", rezultat);

	oslobodiStog(&top);
	return 0;
}

