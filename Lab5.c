#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 50

typedef struct cvor *Stog;
struct cvor {
	char  el;
	Stog next;
};

void push(char x, Stog S);
char pop(Stog S);
char* citajDatoteku();
int racunajPostfix(char* postfix, Stog S);
void ispisStoga(Stog S);

int main(void) {

	struct cvor Head;
	Head.next = NULL;
	char* p;
	int rezultat = 0;

	p = citajDatoteku();
	rezultat = racunajPostfix(p, &Head);
	printf("\n\tRezultat je = %d.\n", rezultat);



	return 0;
}

void ispisStoga(Stog S) {

	while (S->next != NULL) {
		printf(" %c", S->el);
		S = S->next;
	}
}

int racunajPostfix(char* postfix, Stog S) {

	char check[20];
	int n = 0, broj;
	char tempA, tempB;

	do {
		sscanf(postfix, "%s %n", &check, &n);
		postfix += n;


		if (strcmp(check, "+") == 0) {
			tempA = pop(S);
			tempB = pop(S);
			push(tempA + tempB, S);
		}
		else if (strcmp(check, "*") == 0) {
			tempA = pop(S);
			tempB = pop(S);
			push(tempA * tempB, S);
		}
		else {
			sscanf(check, "%d", &broj);
			push(broj, S);
		}




	} while (n != 1);

	return S->el;
}


char* citajDatoteku() {
	FILE *ulz;
	char* data = (char*)malloc(MAX * sizeof(char));

	ulz = fopen("Stog.txt", "r");
	fgets(data, MAX, ulz);
	fclose(ulz);

	if (data) return data;
	return NULL;
}


void push(char x, Stog S) {
	Stog q;
	q = (Stog)malloc(sizeof(struct cvor));
	q->el = x;
	q->next = S->next;
	S->next = q;
}

char pop(Stog S) {
	char x;
	Stog temp;
	if (S->next == NULL) {
		printf("Stog prazan.");
		return -1;
	}
	if (S->next != NULL) {
		x = S->next->el;
		temp = S->next;
		S->next = temp->next;
		free(temp);
	}
	return x;
}