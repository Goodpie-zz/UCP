#include <stdlib.h>
#include <stdio.h>

#include "linkedlist.h"

/**
 * SUBMODULE: createLinkedList
 * IMPORT: None
 * EXPORT: linkedList
 * Creates a new linked list
 */
LinkedList* createLinkedList()
{
    LinkedList* linkedList = (LinkedList*) malloc(sizeof(LinkedList));

    /* Default all values to null */
    linkedList->head = NULL;
    linkedList->tail = NULL;
    linkedList->size = 0;

    return linkedList;
}

/**
 * SUBMODULE: insertFirst
 * IMPORT: linkedList, value
 * EXPORT: None
 * Inserts an element into the head of the linked list
 */
void insertFirst(LinkedList* linkedList, void* value)
{
    /* Create a new node */
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->value = value;
    newNode->prev = NULL;

    if (linkedListIsEmpty(linkedList))
    {
        /* First element, set as head and tail */
        newNode->next = NULL;
        linkedList->head = newNode;
        linkedList->tail = newNode;
    }
    else
    {
        /* Swap places with prev head */
        newNode->next = linkedList->head;
        linkedList->head->prev = newNode;
        linkedList->head = newNode;
    }

    /* Increment size */
    linkedList->size += 1;
}

/**
 * SUBMODULE: insertLast
 * IMPORT: linkedList, value
 * EXPORT: None
 * Inserts an element into the tail of the linked list
 */
void insertLast(LinkedList* linkedList, void* value)
{
    /* Create a new node */
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    if (linkedListIsEmpty(linkedList))
    {
        /* First element, insert first */
        newNode->prev = NULL;
        linkedList->head = newNode;
        linkedList->tail = newNode;
    }
    else
    {
        /* Swap places with previous tail */
        newNode->prev = linkedList->tail;
        linkedList->tail->next = newNode;
        linkedList->tail = newNode;
    }

    /* Increment size */
    linkedList->size += 1;
}

/**
 * SUBMODULE: removeFirst
 * IMPORT: linkedList
 * EXPORT: headNode
 * Removes the head node from the linked list
 */
Node* removeFirst(LinkedList* linkedList)
{
    /* Default node to return */
    Node* headNode = NULL;

    if (!linkedListIsEmpty(linkedList))
    {
        headNode = linkedList->head;
        /* Check not a single element list */
        if (headNode->next != NULL)
        {
            headNode->next->prev = NULL;
        }
        linkedList->head = headNode->next;

        /* Only decrement if we remove element */
        linkedList->size -= 1;
    }

    return headNode;
}

/**
 * SUBMODULE: removeLast
 * IMPORT: linkedList
 * EXPORT: tailNode
 * Removes the tail node of the linked list
 */
Node* removeLast(LinkedList* linkedList)
{
    /* Default node to return */
    Node* tailNode = NULL;

    if (!linkedListIsEmpty(linkedList))
    {
        tailNode = linkedList->tail;
        /* Check not a single element list */
        if (tailNode->prev != NULL)
        {
            tailNode->prev->next = NULL;
        }
        linkedList->tail = tailNode->prev;

        /* Only decrement if we remove an element */
        linkedList->size -= 1;
    }

    return tailNode;
}

/**
 * SUBMODULE: findIndex
 * IMPORT: linkedList, index
 * EXPORT: node
 * Gets Node at index from linkedList
 */
Node* findIndex(LinkedList* linkedList, int index)
{
    Node* node = NULL;
    int count;

    /* Check index in range */
    if ((index < linkedList->size) && (index >= 0))
    {
        count = 0;
        node = linkedList->head;
        while (count < index)
        {
            node = node->next;
            count ++;
        }
    }

    return node;

}

/**
 * SUBMODULE: linkedListIsEmpty
 * IMPORT: linkedList
 * EXPORT: (int) boolean
 * Function more for readability
 */
int linkedListIsEmpty(LinkedList* linkedList)
{
    return linkedList->size == 0;
}

/**
 * SUBMODULE: freeLinkedList
 * IMPORT: LinkedList* linkedList
 * EXPORT: None
 * Frees all elements within the linkedList
 */
void freeLinkedList(LinkedList* linkedList)
{
    Node *currentNode, *nextNode;
    currentNode = linkedList->head;

    /* Iterate through the list */
    while (currentNode != NULL)
    {
        nextNode = currentNode->next;
        free(currentNode->value);
        free(currentNode);
        currentNode = nextNode;
    }

    free(linkedList);
}
