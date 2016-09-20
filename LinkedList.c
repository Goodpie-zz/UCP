#include <stdlib.h>
#include "LinkedList.h"

LinkedList* createLinkedList(void* value)
{
	Node* newNode;
	LinkedList* list;

	newNode = (Node*) malloc(sizeof(Node));
	(*newNode).value = value;
	(*newNode).next = NULL;

	list = (LinkedList*) malloc(sizeof(LinkedList));
	(*list).head = newNode;
	(*list).tail = newNode;
	(*list).size = 1;

	return list;
	 
}

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
	
	/* Increase size */
	(*list).size += 1;
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

	/* Increase size */
	(*list).size += 1;
	
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

void* removeLast(LinkedList* list)
{
	Node* current;
	Node* prev;
	void* value;

	current = (*list).head;
	/* Loop through until we find the last element */
	while ((*current).next != NULL)
	{
		prev = current;
		current = (*current).next;
	}

	value = (*current).value;
	(*prev).next = NULL;
	free(current);
	
	return value;

}

void* removeFirst(LinkedList* list)
{
	Node* tmp = (*list).head;
	if (tmp->next != NULL)
	{
		list->head = tmp->next;
	}

	return tmp->value;
}

void deleteList(LinkedList* list)
{
	Node* current = (*list).head;
	Node* tmp;

	while ((*current).next != NULL) 
	{
		tmp = current;
		current = (*tmp).next;
		free(tmp);
	}

	free(current);
	free(list);
}
