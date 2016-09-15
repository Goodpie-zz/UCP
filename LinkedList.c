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
	while (current != NULL)
	{
		current = (*current).next;
	}

	/* Now inset a new node to the end of the linked list */
	newNode = (Node*) malloc(sizeof(node));
	(*newNode).next = NULL;
	(*newNode).value = value;	
	(*current).next = newNode;
}


