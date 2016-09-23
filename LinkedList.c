#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"

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
    tmp->next->prev = NULL;

    linkedList->size -= 1;
	
	free(tmp);
}

void removeLast(LinkedList* linkedList)
{
	Node* tmp;

	tmp = linkedList->tail;
	linkedList->tail = tmp->prev;
    tmp->prev->next = NULL;

    linkedList->size -= 1;

	free(tmp);
}

void deleteList(LinkedList* linkedList)
{
	Node* current;

	current = linkedList->head;

	while (current->next != NULL)
	{
		printf("Freeing: %d\n", *(int*) (current->value));
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

