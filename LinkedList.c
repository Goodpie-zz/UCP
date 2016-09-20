#include <stdlib.h>
#include "LinkedList.h"

LinkedList* createLinkedList(void* value)
{
	Node* newNode;
	LinkedList* list;

	newNode = (Node*) malloc(sizeof(Node));
	newNode->value = value;
	newNode->next = NULL;
	newNode->prev = NULL; /* Head will always have prev of NULL */

	list = (LinkedList*) malloc(sizeof(LinkedList));
	list->head = newNode;
	list->tail = newNode;
	list->size = 1;

	return list;
}

void insertFirst(LinkedList* list, void* value)
{
	Node* newNode;

	/* Create the new node and store the head in a temp variable */ 
	newNode = (Node*) malloc(sizeof(Node));
	
	newNode->next = list->head;
	newNode->prev = NULL;
	newNode->value = value;

	/* Change the current head value */
	list->head->prev = newNode;
	list->head = newNode;
	
	/* Increase size */
	list->size += 1;
}

void insertLast(LinkedList* list, void* value)
{
	Node* current;
	Node* newNode;
	
	current = list->head;

	/* Traverse the list until we get to the last node */
	while (current->next != NULL)
	{
		current = current->next;
	}

	/* Create a new node */
	newNode = (Node*) malloc(sizeof(Node));

	newNode->next = NULL;
	newNode->prev = current;
	newNode->value = value;

	/* Update the previous last item */
	current->next = newNode;

	free(newNode);

	/* Increase size */
	list->size += 1;
	
}

void* peakFirst(LinkedList* list)
{
	Node* head = list->head;
	return head->value;
}

void* peakLast(LinkedList* list)
{
	Node* current = list->head;

	/* Traverse until we find the last element in list */
	while (current->next != NULL)
	{
		current = current->next;
	}

	/* Return last value in the list */
	return current->value;
}

void* removeLast(LinkedList* list)
{
	Node* current;
	Node* prev;
	void* value;
	
	current = list->head;

	while(current->next != NULL)
	{
		current = current->next;
	}

	prev = current->prev;
	value = current->value;

	prev->next = NULL;
	free(prev->next);

	list->size -= 1;
	list->tail = prev;

	return value;
}

void* removeFirst(LinkedList* list)
{
	Node* head;
	void* value;

	head = list->head;
	value = head->value;
	head->next->prev = NULL;
	head->next = NULL;
	free(head);

	list->size -= 1;

	return value;
}

void deleteList(LinkedList* list)
{
	Node* current = list->head;
	Node* tmp;

	while (current->next != NULL) 
	{
		tmp = current;
		current = tmp->next;
		free(tmp);
	}

	free(current);
	free(list);
}
