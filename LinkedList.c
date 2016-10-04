#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"

/** 
 * 	SUBMODULE: createLinkedList
 * 	IMPORT: None EXPORT: LinkedList*
 * 	Creates a LinkedList allocating memory to the first Node
 */
LinkedList* createLinkedList()
{
	LinkedList* linkedList;
    Node* newNode;

	/* Assign memory to LinkedList */
	linkedList = (LinkedList*) malloc(sizeof(LinkedList));

    newNode = (Node*) malloc(sizeof(Node));
	
	/* Assign default LinkedList Attributes */
	linkedList->head = newNode;
	linkedList->tail = newNode;
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
    Node* newNode;
    Node* prevHead;
    
    if (linkedList->size == 0)
    {
        newNode = linkedList->head;
        newNode->value = value;
        newNode->prev = NULL;
        newNode->next = NULL;
    }
    else
    {
        newNode = (Node*) malloc(sizeof(Node));

        prevHead = linkedList->head;

        newNode->next = prevHead;
        newNode->prev = NULL;

        prevHead->prev = newNode;

        linkedList->head = newNode;
    }

    linkedList->size += 1;

}

/**
 * SUBMODULE: insertLast
 * IMPORT LinkedList*, void* EXPORT None
 * Inserts a void* value into the tail of the linked list
 */
void insertLast(LinkedList* linkedList, void* value)
{
    Node* newNode;
    Node* prevTail;

    if (linkedList->size == 0)
    {
        insertFirst(linkedList, value);
    }
    else
    {
        newNode = (Node*) malloc(sizeof(Node));
        
        prevTail = linkedList->tail;

        newNode->next = NULL;
        newNode->prev = prevTail;

        linkedList->tail = newNode;
        prevTail->next = newNode;  
    }

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
    tmp->next->prev = NULL;

    linkedList->size -= 1;
	
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
    tmp->prev->next = NULL;

    linkedList->size -= 1;

	free(tmp);
}

/**
 * SUBMODULE findIndex
 * IMPORT LinkedList*, int EXPORT void*
 * Returns the value at the given index within the linked list
 */
void* findIndex(LinkedList* linkedList, int index)
{
	int i;
	Node* current;
	void* value;

	current = linkedList->head;

	/* Traverse the linked list until index is found */
	if (index >= linkedList->size)
	{
		value = NULL;
	}
	else
	{
		for (i = 0; i < index; i ++)
		{
			current = current->next;
		}

		value = current->value;
	}

	return value;
}

/**
 * SUBMODULE: deleteList
 * IMPORT LinkedList* EXPORT None
 * Frees all memory currently allocated to the linked list
 */ 
void freeList(LinkedList* linkedList)
{
	Node* current;

	current = linkedList->head;

	while (current->next != NULL)
	{
		printf("Freeing: %d\n", *(int*) (current->value));
		free(current->value);
        current = current->next;
		free(current->prev);
	}

	free(current->value);
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

