#include <stdlib.h>
#include "LinkedList.h"

void insertFirst(LinkedList* list, void* value)
{
	Node* tmp;
	Node* newNode;

	/* Create the new node and store the head in a temp variable */ 
	newNode = (Node*) malloc(sizeof(Node));
	tmp = (*list).head;
	
	/* Assign new nodes next to be the previous head and the linked list head to the new node */
	(*newNode).next = tmp;
	(*list).head = newNode;
}

void insertLast(LinkedList* list, void* value)
{
	Node* current;
	Node* newNode;
	
	current = (*list).head;

	/* Traverse the list until we get to the last node */
	while ((*current).next != NULL)
	{
		current = (*current).next;
	}

	/* Now inset a new node to the end of the linked list */
	newNode = (Node*) malloc(sizeof(Node));
	(*newNode).next = NULL;
	(*newNode).value = value;	
	(*current).next = newNode;
	
}

void* peakFirst(LinkedList* list)
{
	Node* head = (*list).head;
	return (*head).value;
}

void* peakLast(LinkedList* list)
{
	Node* current = (*list).head;

	/* Traverse until we find the last element in list */
	while ((*current).next != NULL)
	{
		current = (*current).next;
	}

	/* Return last value in the list */
	return (*current).value;
}

void deleteList(LinkedList* list)
{
	Node* current = (*list).head;
	while ((*current).next == NULL)
	{
		Node* tmp = current;
		current = (*tmp).next;
		
		/* Free the tmp */
		free((*tmp).value);
		free(tmp);
	}
	
	free(current);
}

