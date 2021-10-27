#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_SUCCESS 1
#define MAX_NAME (256)

struct _person;
typedef struct _person* Position;
typedef struct _person {
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	int birthYear;
	Position next;
}Person;

int insertInformation(Position p);
Position createStudent(char* firstName, char* lastName, int birthYear);
int insertBeginning(Position where, Position what);
int insertEnd(Position where, Position what);
int printList(Position head);
Position findElement(Position q, char* lN);
Position findPrevious(Position p, char* previous);
int deleteElement(Position p, char* lastN);

int main(void) {
	Person head;
	Position q = NULL;
	Position p = NULL;

	char choose = 0;
	char lastN = 0;
	head.next = NULL;


	while (choose != 'K' && choose != 'k')
	{
		printf("\r\Type in:");
		printf("\r\n\t0 - enter person's info");
		printf("\r\n\t1 - enter a person in the beginning");
		printf("\r\n\t2 - print the list");
		printf("\r\n\t3 - enter a person on the end");
		printf("\r\n\t4 - search the person by last name");
		printf("\r\n\t5 - delete");
		printf("\r\n\tk - end\r\n\n\t");

		scanf(" %c ", &choose);

		switch (choose)
		{
		case '0':
			insertInformation(&head);
			break;
		case '1':
			insertBeginning(&head, p);
			break;
		case '2':
			printList(head.next);
			break;
		case '3':
			insertEnd(&head, p);
			break;
		case '4':
			printf("\r\nEnter the last name of the person you want to find:");
			scanf(" %s ", lastN);
			q = findElement(head.next, &lastN);
			if (NULL == q)
				printf("\r\nTry again..");
			else
				printf("\r\n\t%s %s, %d", q->firstName, q->lastName, q->birthYear);
			break;
		case '5':
			printf("\r\nEnter the last name of the person you want to delete:");
			scanf(" %s ", lastN);
			if (NULL == q)
				printf("\r\nTry again..");
			deleteElement(&head, &lastN);
			break;
		case 'k':
		case 'K':
			printf("\r\nThe end!!!\n");
			break;
		default:
			printf("\r\nYou failed!!! Try again..\n");
		}



		return EXIT_SUCCESS;
	}

}
int insertInformation(Position p) {

	char firstName[MAX_NAME] = { 0 };
	char lastName[MAX_NAME] = { 0 };
	int birthYear = 0;
	printf("\n\rPlease insert person's info:\r\n");

	printf("First name:\t\n");
	scanf(" %s ", firstName);

	printf("Last name:\t\n");
	scanf(" %s ", lastName);

	printf("Birth year:\t\n");
	scanf(" %d ", &birthYear);

	p = createStudent(firstName, lastName, birthYear);
	return 0;
}


Position createStudent(char* firstName, char* lastName, int birthYear) {
	Position p = NULL;

	p = (Position)malloc(sizeof(Person));

	if (!p) {
		printf("Memory allocation failed!\r\n");
		return NULL;
	}
	strcpy(p->firstName, firstName);
	strcpy(p->lastName, lastName);
	p->birthYear = birthYear;
	return p;
}

int insertBeginning(Position where, Position what) {
	what->next = where->next;
	where->next = what;
	return 0;
}

int printList(Position head) {
	Position p = NULL;

	printf("List content:\r\n");

	for (p = head->next; p != NULL; p = p->next) {
		printf("\t%s %s %d\r\n", p->firstName, p->lastName, p->birthYear);
		p = p->next;
	}

	printf("\r\n");
	return 0;
}

int insertEnd(Position where, Position what) {
	while (where->next != NULL) {
		where = where->next;
	}
	insertBeginning(where, what);
	return 0;
}

Position findElement(Position q, char* lN) {
	while (q->next != NULL && strcmp(q->lastName, lN)) {
		q = q->next;
	}
	return q;
}
Position findPrevious(Position p, char* previous) {
	Position prev = p;
	p = p->next;

	while (p->next != NULL && strcmp(p->lastName, previous)) {
		prev = p;
		p = p->next;
	}
	if (p->next == NULL) {
		printf("Doesn't exist.\r\n");
		return NULL;
	}
	return prev;
}

int deleteElement(Position p, char* previous) {
	Position prev;
	prev = findPrevious(p, previous);

	if (prev != NULL) {
		p = prev->next;
		prev->next = p->next;
		printf("\r\nPerson %s %s has been deleted from the list.", p->firstName, p->lastName);
		free(p);
	}
	else
		printf("\r\nPerson doesn't exist.");
	return 0;

}