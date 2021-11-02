#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 32
#define MAX_ROW 128

struct _node;
typedef struct _node* Pozicija;
typedef struct _node {
	char ime[MAX];
	char prezime[MAX];
	int godiste;
	Pozicija next;
} Node;

Pozicija kreirajOsobu();
int unesiPodatke(Pozicija);
int DodajPocetak(Pozicija);
int DodajKraj(Pozicija);
int Ispis(Pozicija);
int DodajIza(Pozicija);
int pronadiPrezime(Pozicija);
int brisanje(Pozicija);
int PronalaziPrethodnika(Pozicija);
int DodajIspred(Pozicija);
int upisUdatoteku(Pozicija);
int citajDatoteku();
int sortiranje(Pozicija);


int main() {
	Node head;
	head.next = NULL;
	int input = -1;


	while (input != 0) {
		//IspisiMenu();
		scanf("%d", &input);

		switch (input) {
		case 1:
			DodajPocetak(&head);
			break;
		case 2:
			DodajKraj(&head);
			break;
		case 3:
			Ispis(&head);
			break;
		case 4:
			DodajIza(&head);
			break;
		case 6:
			pronadiPrezime(&head);
			break;
		case 7:
			brisanje(&head);
			break;
		case 5:
			DodajIspred(&head);
			break;
		case 8:
			upisUdatoteku(&head);
			break;
		case 9:
			citajDatoteku();
			break;
		case 10:
			sortiranje(&head);
			break;

		}
	}
}

int unesiPodatke(Pozicija temp) {
	printf("--Unesi podatke--\n(ime, prezime, godiste):");
	scanf(" %s %s %d", temp->ime, temp->prezime, &temp->godiste);
	temp->next = NULL;
	return 0;
}
Pozicija kreirajOsobu() {
	Pozicija temp = (Pozicija)malloc(sizeof(Node));
	if (temp) {
		unesiPodatke(temp);
		return temp;
	}
	else {
		printf("\n\rGreska alokacije\n\r");
		return NULL;
	}
}

int DodajPocetak(Pozicija head) {
	Pozicija temp = kreirajOsobu();
	temp->next = head->next;
	head->next = temp;
	return 0;
}

int DodajKraj(Pozicija head) {
	Pozicija tempKraj = head->next;
	Pozicija temp = kreirajOsobu();

	if (head->next == NULL) {
		head->next = temp;
		return 0;
	}

	while (tempKraj->next != NULL) {
		tempKraj = tempKraj->next;
	}
	tempKraj->next = temp;
	return 0;
}

int Ispis(Pozicija head) {
	Pozicija temp = head->next;
	printf("\n\t-----Ispis-----\n\n");

	if (!temp) { return -1; }

	else {
		while (temp != NULL) {
			printf("\n\t<%s %s, %d>\n", temp->ime, temp->prezime, temp->godiste);
			temp = temp->next;
		}
	}

	return 0;
}

int DodajIza(Pozicija head) {
	Pozicija Current = head->next;
	Pozicija temp;
	char tempPrez[MAX];

	printf("\nUnesi trazeno prezime: ");
	scanf("%s", tempPrez);

	while (Current != NULL) {
		if (strcmp(Current->prezime, tempPrez) == 0) {
			temp = kreirajOsobu();
			temp->next = Current->next;
			Current->next = temp;
			return 0;
		}
		Current = Current->next;
	}

	printf("Ne postoji trazena osoba. Unesite opet.\n");
	return 0;

}

int pronadiPrezime(Pozicija head) {
	Pozicija temp = head->next;
	char tempPrez[MAX];

	printf("\nUnesi trazeno prezime: ");
	scanf("%s", tempPrez);

	while (temp != NULL) {
		if (strcmp(temp->prezime, tempPrez) == 0) {
			printf("\n\t<%s %s, %d>\n", temp->ime, temp->prezime, temp->godiste);
			return 0;
		}
		temp = temp->next;
	}
	printf("Ne postoji trazena osoba. Unesite opet.\n");
	return 0;
}

int brisanje(Pozicija head) {
	Pozicija temp = head->next;
	Pozicija tempPrev = NULL;
	char tempPrez[MAX];

	if (temp == NULL) {
		printf("Lista je prazna\n");
		return 0;
	}

	printf("\nUnesi prezime osobe: ");
	scanf(" %s", tempPrez);

	if (strcmp(temp->prezime, tempPrez) == 0) {
		head->next = temp->next;
		free(temp);
		return 0;
	}

	while (temp != NULL) {
		//printf("AAAa");

		if (strcmp(temp->prezime, tempPrez) == 0) {
			//printf("AAAa");
			tempPrev->next = temp->next;
			free(temp);
			
			printf("\n\tOsoba je izbrisana.\n");
			return 0;
		}
		tempPrev = temp;
		temp = temp->next;
	}
	printf("Ne postoji trazena osoba. Unesite opet.\n");
	return 0;
}

int PronalaziPrethodnika(Pozicija head){
	Pozicija temp = head->next;
	Pozicija tempPrev = NULL;
	char tempPrez[MAX];

	if (temp == NULL) {
		printf("Lista je prazna.\n");
		return 0;
	}
	printf("\nUnesi prezime osobe: ");
	scanf("%s", tempPrez);

	if (strcmp(temp->prezime, tempPrez) == 0) {
		return 0;
	}

	while (temp != NULL) {
		if (strcmp(temp->prezime, tempPrez) == 0) {
			return tempPrev;
		}
		tempPrev = temp;
		temp = temp->next;
	}
	printf("Ne postoji trazena osoba. Unesite opet.\n");
	return 0;
}

int DodajIspred(Pozicija head) {
	Pozicija tempPrev;
	Pozicija temp;

	tempPrev = PronalaziPrethodnika(head);
	
	if (tempPrev == NULL) {
		DodajPocetak(head);
		return 0;
	}
	else {
		temp = kreirajOsobu();
		temp->next = tempPrev->next;
		tempPrev->next = temp;
		return 0;
	}
	return 0;
}

int upisUdatoteku(Pozicija head) {
	Pozicija temp = head->next;
	FILE* ulz;
	ulz = fopen("osobe.txt", "w");

	if (ulz == NULL) {
		printf("\n\tGreska kod otvaranja datoteke.\n");
		return 0;
	}

	
	while (temp != NULL) {
		fprintf(ulz, " %s %s %d\n", temp->ime, temp->prezime, temp->godiste);
		temp = temp->next;
	}
	fclose(ulz);
	printf("\n\tOsobe upisane.\n");
	return 0;
}

int citajDatoteku() { //kod citanja i ispisa procitanog, prvu upisanu osobu ispise dva puta???
	FILE* ilz;
	char red[MAX_ROW];

	ilz = fopen("osobe.txt", "r");
	
	if (ilz == NULL) {
		printf("\n\tGreska kod otvaranja datoteke.\n");
		return 0;
	}

	while (!feof(ilz)) {
		fgets(red, 100, ilz);
		printf(" %s ", red);
	}
	fclose(ilz);
	return 0;

}

int sortiranje(Pozicija head) { //zasto zadnju upisanu osobu nakon sortiranja nemamo u listi?
	Pozicija temp = NULL;
	Pozicija tempPrev = NULL;
	Pozicija i, j, kraj;
	kraj = NULL;
	i = head->next;

	if (head->next == NULL) {
		printf("\n\tLista je prazna.\n");
		return 0;
	}

	while (i != kraj) {
		tempPrev = i;
		j = i;
		while (j->next != kraj) {
			if (strcmp(j->prezime, j->next->prezime) > 0) {
				temp = j->next;
				tempPrev = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}

			tempPrev = j;
			j = j->next;
		}

		kraj = j;
	}
	printf("\n\tLista je sortirana.\n");
			return 0;
}