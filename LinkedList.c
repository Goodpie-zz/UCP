#include <stdlib.h>
#include "LinkedList.h"


/** 
 * 	SUBMODULE: createLinkedList
 * 	IMPORT: None EXPORT: LinkedList*
 * 	Creates a LinkedList allocating memory to the first Node
 */
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

/**
 * SUBMODULE: insertFirst
 * IMPORT: LinkedList*, void* EXPORT: None
 * Inserts a void* value into the haed of the LinkedList
 */
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

/**
 * SUBMODULE: insertLast
 * IMPORT LinkedList*, void* EXPORT None
 * Inserts a void* value into the tail of the linked list
 */
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

/**
 * SUBMODULE: peekFirst
 * IMPORT LinkedList* EXPORT void*
 * Retrieves the first element of the LinkedList without deleting it
 */ 
void* peekFirst(LinkedList* linkedList)
{
	return linkedList->head->value;
}

/**
 * SUBMODULE: peekLast
 * IMPORT LinkedList* EXPORT void*
 * Retrieves the last element of the LinkedList without deleting it
 */ 
void* peekLast(LinkedList* linkedList)
{
	return linkedList->tail->value;
}

/**
 * SUBMODULE: removeFirst
 * IMPORT LinkedList* EXPORT None
 * Removes the first element of the linked list
 */ 
void removeFirst(LinkedList* linkedList)
{
	Node* tmp;

	tmp = linkedList->head;
	linkedList->head = tmp->next;
	
	free(tmp);
}

/**
 * SUBMODULE: removeLastt
 * IMPORT LinkedList* EXPORT None
 * Removes the last element of the linked list
 */ 
void removeLast(LinkedList* linkedList)
{
	Node* tmp;

	tmp = linkedList->tail;

	linkedList->tail = tmp->prev;

	free(tmp);
}

/**
 * SUBMODULE: deleteList
 * IMPORT LinkedList* EXPORT None
 * Frees all memory currently allocated to the linked list
 */ 
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

/*
 * SUBMODULE: listIsEmpty
 * IMPORT LinkedList* EXPERT int (bool)
 * Checks whether the current linked list is empty or not
 */
int listIsEmpty(LinkedList* linkedList)
{
	int isEmpty = 0;

	if ((linkedList->head = NULL))
	{
		isEmpty = 1;
	}

	return isEmpty;
}

