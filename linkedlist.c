#include <stdlib.h>
#include <stdio.h>

#include "linkedlist.h"

LinkedList* createLinkedList()
{
    LinkedList* linkedList;
    Node* node;

    /* Assign memory to linked list */
    linkedList = (LinkedList*) malloc(sizeof(LinkedList));

    /* Assign memory to head node */
    node = (Node*) malloc(sizeof(Node));

    /* Assign default values */
    linkedList->head = node;
    linkedList->tail = node;
    linkedList->size = 0;

    return linkedList;
}

void freeLinkedList(LinkedList* linkedList)
{
    /* Start at tail end */
    Node* tmp;
    Node* currentNode = linkedList->tail;

    while(currentNode->prev != NULL)
    {
        tmp = currentNode;
        currentNode = tmp->prev;
        freeNode(tmp);
    }

    /* Free head node and list */
    freeNode(currentNode);
    free(linkedList);
}

void insertFirst(LinkedList* linkedList, void* value)
{
    Node* node;
    Node* prevHead = linkedList->head;

    if (linkedList->size == 0)
    {
        prevHead->value = value;
        prevHead->prev = NULL;
        prevHead->next = NULL;
    }
    else
    {
        node = (Node*) malloc(sizeof(Node));
        node->next = prevHead;
        node->prev = NULL;

        prevHead->prev = node;

        linkedList->head = node;
    }

    linkedList->size += 1;
}

void insertLast(LinkedList* linkedList, void* value)
{
    Node* node;
    Node* prevTail = linkedList->tail;

    if (linkedList->size == 0)
    {
        insertFirst(linkedList, value);
    }
    else
    {
        node = (Node*) malloc(sizeof(Node));
        node->next = NULL;
        node->prev = prevTail;

        prevTail->next = node;

        linkedList->tail = node;
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
    Node* prevHead = linkedList->head;

    prevHead->next->prev = NULL;
    linkedList->head = prevHead->next;

    linkedList->size -= 1;
    freeNode(prevHead);
}

void removeLast(LinkedList* linkedList)
{
    Node* prevTail = linkedList->tail;

    prevTail->prev->next = NULL;
    linkedList->tail = prevTail->prev;

    linkedList->size -= 1;

    freeNode(prevTail);
}

void freeNode(Node* node)
{
    free(node);
}

