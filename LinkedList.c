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
    Node* newNode;
    Node* prevHead;

    newNode = (Node*) malloc(sizeof(Node));

    prevHead = linkedList->head;

    newNode->next = prevHead;
    newNode->prev = NULL;

    linkedList->head = newNode;
    linkedList->size += 1;

}

void insertLast(LinkedList* linkedList, void* value)
{
    Node* newNode;
    Node* prevTail;

    newNode = (Node*) malloc(sizeof(Node));
    
    prevTail = linkedList->tail;

    newNode->next = NULL;
    newNode->prev = prevTail;

    linkedList->tail = newNode;
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

