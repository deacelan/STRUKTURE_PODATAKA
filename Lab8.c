#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>


typedef struct node* Position;
struct node {
	int number;
	Position left;
	Position right;
};

Position addNumber(int, Position);
Position printIn(Position P);
Position printPre(Position P);
Position printPost(Position P);
Position findMax(Position);
Position findMin(Position);
Position findNumber(int, Position);
Position deleteNumber(int, Position);

int main()
{
	Position root = NULL, x = NULL;
	int a, num;

	do {
		printf("\n\n1 - Add new number to the tree \n");
		printf("2 - Display the tree inorder\n");
		printf("3 - Display the tree preorder\n");
		printf("4 - Display the tree postorder\n");
		printf("5 - Search number\n");
		printf("6 - Delete number\n");
		printf("0 - Exit\n");

		printf("\n Enter your choice: \n");
		scanf(" %d", &a);

		switch (a)
		{
		case 1:
			printf("\nAdd new number: \n");
			scanf(" %d", &num);
			root = addNumber(num, root);
			if (root == NULL) printf("Error.\n");
			break;

		case 2:
			x = printIn(root);
			if (x == NULL) printf("The tree is empty.\n");
			break;

		case 3:
			x = printPre(root);
			if (x == NULL) printf("The tree is empty.\n");
			break;

		case 4:
			x = printPost(root);
			if (x == NULL) printf("The tree is empty.\n");
			break;

		case 5:
			printf("\nSearch element: \n");
			scanf(" %d", &num);
			x = findNumber(num, root);
			if (x == NULL) printf("Number does not exist.\n");
			else printf("Number %d is found.\n", x->number);
			break;

		case 6:
			printf("\nPick the number you want to delete: \n");
			scanf(" %d", &num);
			root = deleteNumber(num, root);
			if (root == NULL) printf("Error.\n");
			break;

		case 0:
			printf("\n Exit. \n");
			break;

		default:
			printf("\nError! Try again.\n");
		}

	} while (a != 0);

}

Position addNumber(int x, Position P)
{
	if (P == NULL)
	{
		P = (Position)malloc(sizeof(struct node));
		if (P == NULL) return NULL;
		P->number = x;
		P->left = P->right = NULL;
	}

	else if (x < P->number)
		P->left = addNumber(x, P->left);

	else if (x > P->number)
		P->right = addNumber(x, P->right);

	else
		printf("Element already exists.\n");

	return P;
}
Position printIn(Position P) //inorder
{
	if (NULL == P)
		return P;

	printIn(P->left);
	printf("%d ", P->number); //ako je ovo prvo preorder
	printIn(P->right); //ako je obrnuto right i left onda je postorder

	return P;
}
Position printPre(Position P) //preorder
{
	if (NULL == P)
		return P;

	printf("%d ", P->number);
	printPre(P->left);
	printPre(P->right); 

	return P;
}
Position printPost(Position P) //postorder
{
	if (NULL == P)
		return P;

	printPost(P->right);
	printf("%d ", P->number); 
	printPost(P->left);
	return P;
}

Position findMin(Position P)
{
	if (P != NULL)
	{
		if (P->left != NULL)
		{
			while (P->left != NULL)
				P = P->left;
		}
	}

	return P;
}

Position findMax(Position P)
{
	if (P != NULL)
	{
		if (P->right != NULL)
		{
			while (P->right != NULL)
				P = P->right;
		}
	}

	return P;
}

Position findNumber(int x, Position P)
{
	if (P == NULL) return NULL;

	if (x < P->number)
		return findNumber(x, P->left);
	else if (x > P->number)
		return findNumber(x, P->right);
	else
		return P;
}

Position deleteNumber(int x, Position P)
{
	Position tmp = NULL;

	if (P != NULL)
	{
		if (x < P->number)
			P->left = deleteNumber(x, P->left);
		else if (x > P->number)
			P->right = deleteNumber(x, P->right);
		else
		{
			if (P->right != NULL && P->left != NULL)
			{
				tmp = findMin(P->right);
				P->number = tmp->number;

				P->right = deleteNumber(tmp->number, P->right);
			}
			else
			{
				tmp = P;

				if (P->left != NULL)
					P = P->right;
				else
					P = P->left;
				free(tmp);
			}
		}
	}
	return P;
}