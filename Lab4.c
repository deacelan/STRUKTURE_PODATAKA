
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Polinom* Poly;
struct Polinom {
	int koef;
	int pot;
	Poly next;
};


void unosK(Poly P, int koef, int pot);
void ispis(Poly P);
void suma(Poly P1, Poly P2, Poly S);
void unos(Poly P, int koef, int pot);
void produkt(Poly P1, Poly P2, Poly P);

int main(void)
{
	struct Polinom head, Head, S, P;
	head.next = NULL;
	Head.next = NULL;
	S.next = NULL;
	P.next = NULL;

	unos(&head, 3, 0);
	unos(&head, 4, 1);
	unos(&head, 2, 2);
	ispis(head.next);
	printf("\n\r");

	unos(&Head, 2, 0);
	unos(&Head, 3, 2);
	unos(&Head, 4, 3);
	ispis(Head.next);

	suma(&head, &Head, &S);

	printf("\n\rSuma polinoma je: ");
	ispis(S.next);

	printf("\n\rProdukt polinoma je: ");
	produkt(&head, &Head, &P);
	ispis(P.next);


	return 0;
}

void produkt(Poly P1, Poly P2, Poly P) {
	while (P1 != NULL) {
		while (P2 != NULL) {
			unosK(P, P1->koef * P2->koef, P1->pot + P2->pot);
			P2 = P2->next;
		}
		P1 = P1->next;
	}

}
void suma(Poly P1, Poly P2, Poly S) {
	Poly temp;
	while (P1 != NULL && P2 != NULL) {
		if (P1->pot == P2->pot) {
			unosK(S, P1->koef + P2->koef, P1->pot);
			P1 = P1->next;
			P2 = P2->next;
		}
		else if (P1->pot > P2->pot) {
			unosK(S, P1->koef, P1->pot);
			P1 = P1->next;
		}
		else {
			unosK(S, P2->koef, P2->pot);
			P2 = P2->next;
		}
	}
	//do kraja punimo S sa P1 ili P2 
	if (P1 != NULL) temp = P1;
	else temp = P2;
	while (temp != NULL) {
		unosK(S, temp->koef, temp->pot);
		temp = temp->next;
	}

}

void unosK(Poly P, int koef, int pot) {
	while (P->next != NULL)
		P = P->next;
	unos(P, koef, pot);
}

void ispis(Poly P) {
	printf("%dx^%d", P->koef, P->pot);
	P = P->next;
	while (P != NULL) {
		printf(" %d^x%d", P->koef, P->pot);
		P = P->next;
	}
}

void unos(Poly P, int koef, int pot) {
	Poly q;

	q = (Poly)malloc(sizeof(struct Polinom));
	q->koef = koef;
	q->pot = pot;
	q->next = P->next;
	P->next = q;
}