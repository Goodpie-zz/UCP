#include <stdlib.h>
#include "LinkedList.h"

LinkedList* createLinkedList()
{
	LinkedList* linkedList;

	/* Assign memory to LinkedList */
	linkedList = (LinkedList*) malloc(sizeof(LinkedList));
	
	/* Assign default LinkedList Attributes */
	linkedList->head = NULL;
	linkedList->tail = NULL;
	linkedList->size = 0;

	return linkedList;
}

void insertFirst(LinkedList* linkedList, void* value)
{
	Node* node;

	/* Assign memory to a new Node */
	node = (Node*) malloc(sizeof(Node));

	node->next = NULL;
	node->prev = NULL;
	node->value = value;

	/* Check if LinkedList is new */
	if (listIsEmpty(linkedList))
	{
		linkedList->head = node;
		linkedList->tail = node;
	}
	else
	{
		/* LinkedList is not empty */
		node->next = linkedList->head;
		linkedList->head->prev = node;
		linkedList->head = node;
	}

	/* Increase size of LinkedList */
	linkedList->size += 1;
}

void insertLast(LinkedList* linkedList, void* value)
{
	Node* node;

	/* Assign memory to a new Node */
	node = (Node*) malloc(sizeof(Node));
	
	node->next = NULL;
	node->prev = NULL;
	node->value = value;

	/* Check if linked list is empty */
	if (listIsEmpty(linkedList))
	{
		linkedList->head = node;
		linkedList->tail = node;
	}
	else
	{
		/* LinkedList is not empty */
		node->prev = linkedList->tail;
		linkedList->tail->next = node;
		linkedList->tail = node;
	}

	/* Increase size of LinkedList */
	linkedList->size += 1;
}

void* peekFirst(LinkedList* linkedList)
{
	return linkedList->head->value;
}

void* peekLast(LinkedList* linkedList)
{
	return linkedList->tail->value;
}

void removeFirst(LinkedList* linkedList)
{
	Node* tmp;

	tmp = linkedList->head;
	linkedList->head = tmp->next;
	
	free(tmp);
}

void removeLast(LinkedList* linkedList)
{
	Node* tmp;

	tmp = linkedList->tail;

	linkedList->tail = tmp->prev;

	free(tmp);
}

void deleteList(LinkedList* linkedList)
{
	Node* current;

	current = linkedList->head;

	while (current->next != NULL)
	{
		current = current->next;
		free(current->prev);
	}

	free(current);
	free(linkedList);
}

int listIsEmpty(LinkedList* linkedList)
{
	int isEmpty = 0;

	if ((linkedList->head = NULL))
	{
		isEmpty = 1;
	}

	return isEmpty;
}

