#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node* Directory;
typedef struct stog* Position;

struct node {
	char name[20];
	Directory sibling;
	Directory child;
};

struct stog {
	Directory data;
	Position next;
};

Directory createNewTree();
Position createMoreSpace();
int mkdir(Directory S, char ime[]);
int dir(Directory S);
int Push(Directory S, Position P);
Directory Pop(Position P);
Directory cddir(Directory S, Position P, char ime[]);

int main()
{
	Directory root;
	Directory current;
	root = createNewTree();
	current = createNewTree();
	current = root;
	int x = 9;
	char temp[20];
	Position head;
	head = createMoreSpace();
	strcpy(root->name, "root");

	while (x)
	{
		printf("1 - md\n");
		printf("2 - cd dir\n");
		printf("3 - cd..\n");
		printf("4 - dir\n");
		printf("0 - izlaz\n");
		printf("\nChoice:\n\n");
		scanf(" %d", &x);

		switch (x)
		{
		case 1:
			printf("Enter directory name:\n");
			scanf(" %s", temp);
			mkdir(current, temp);
			break;
		case 2:
			printf("Enter directory name:\n");
			scanf(" %s", temp);
			current = cddir(current, head, temp);
			break;
		case 3:
			current = Pop(head);
			break;
		case 4:
			dir(current);
			break;
		case 0:
			printf("Exit.\n");
			break;
		default:
			printf("Wrong! Try again!\n");
			break;
		}
	}

	return 0;
}

Directory createNewTree()
{
	Directory temp = NULL;
	temp = (Directory)malloc(sizeof(struct node));
	temp->child = NULL;
	temp->sibling = NULL;
	strcpy(temp->name, " ");

	if (!temp)
	{
		printf("Unable to allocate memory.\n");
		return temp;
	}

	return temp;
}

Position createMoreSpace()
{
	Position temp = NULL;
	temp = (Position)malloc(sizeof(struct stog));
	temp->next = NULL;
	temp->data = NULL;

	if (!temp)
	{
		printf("Unable to allocate memory.\n");
		return temp;
	}

	return temp;
}

int mkdir(Directory S, char ime[])
{
	Directory novi = createNewTree();
	strcpy(novi->name, ime);
	if (S->child == NULL)
		S->child = novi;
	else
	{
		S = S->child;
		if (S->sibling == NULL)
		{
			S->sibling = novi;
		}
		else
		{
			while (S->sibling != NULL)
			{
				S = S->sibling;
			}
			S->sibling = novi;
		}
	}
	return 0;
}

int dir(Directory S)
{
	if (S->child == NULL)
	{
		printf("Empty directory!\n");
	}
	else
	{
		if (S->child->sibling == NULL)
		{
			printf("%s\n", S->child->name);
		}
		else
		{
			S = S->child;
			while (S->sibling != NULL)
			{
				printf("%s\n", S->name);
				S = S->sibling;
			}
			printf("%s\n", S->name);
		}
	}
	return 0;
}

int Push(Directory S, Position P)
{
	Position novi = NULL;

	if (P->next == NULL)
	{
		novi = createMoreSpace();
		novi->data = S;
		P->next = novi;
	}
	else
	{
		while (P->next != NULL)
		{
			P = P->next;
		}

		novi = createMoreSpace();
		novi->data = S;
		P->next = novi;
	}
	return 0;
}

Directory Pop(Position P)
{
	Directory x;
	Position temp;

	while (P->next->next != NULL)
	{
		P = P->next;
	}
	x = P->next->data;
	temp = P->next;
	P->next = temp->next;
	free(temp);

	return x;
}

Directory cddir(Directory S, Position P, char ime[])
{
	Push(S, P);
	Directory glavni = S;

	if (S->child == NULL)
	{
		printf("Empty directory\n");
	}
	else
	{
		S = S->child;
		while (S->sibling != NULL)
		{
			if (!(strcmp(S->name, ime)))
			{
				return S;
			}
			S = S->sibling;
		}

		if (!(strcmp(S->name, ime)))
		{
			printf("You are currently in directory %s\n", ime);
			return S;
		}
		else
		{
			printf("Directory does not exist.\n");
			return glavni;
		}
	}
}
