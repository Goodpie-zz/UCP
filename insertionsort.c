#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "headerinfo.h"
#include "insertionsort.h"
#include "boolean.h"

static void sortByString(int, LinkedList*, int);
static void sortByInteger(int, LinkedList*, int);
static void swapNodes(Node*, Node*);

void sortBy(int headerIndex, HeaderInfo* header, LinkedList* dataList, int order)
{
    printf("%s is type %s\n", header->name, header->type);
    if (strcmp("string", header->type) == 0)
    {
        sortByString(headerIndex, dataList, order);
    }
    else
    {
        sortByInteger(headerIndex, dataList, order);
    }
}

void sortByString(int headerIndex, LinkedList* dataList, int order)
{
    /* TODO: Implement method */
}

void sortByInteger(int headerIndex, LinkedList* dataList, int order)
{
    int currentIndex = 0;
    int correctPosition;
    Node *currentListNode, *previousListNode;
    LinkedList *currentList, *previousList;
    Node *currentNode, *previousNode;
    int *currentValue, *previousValue;

    printf("Order Value: %d\n", order);

    currentListNode = dataList->head;
    while (currentListNode != NULL)
    {
        previousListNode = currentListNode->prev;
        correctPosition = FALSE;
        while ((previousListNode != NULL) && (correctPosition == FALSE))
        {
            currentList = (LinkedList*) currentListNode->value;
            previousList = (LinkedList*) previousListNode->value;

            currentNode = findIndex(currentList, headerIndex);
            previousNode = findIndex(previousList, headerIndex);

            currentValue = (int*) currentNode->value;
            previousValue = (int*) previousNode->value;

            printf("Comparing %d with %d\n", *currentValue, *previousValue);

            if (order == ASCENDING)
            {
                if (*currentValue < *previousValue)
                {
                    printf("%d is less than %d\n", *currentValue, *previousValue);
                    swapNodes(currentListNode, previousListNode);
                }
                else
                {
                    printf("%d not less than %d\n", *currentValue, *previousValue);
                    correctPosition = TRUE;
                }
            }
            else if (order == DESCENDING)
            {
                if (*currentValue > *previousValue)
                {
                    printf("%d is more than %d\n", *currentValue, *previousValue);
                    swapNodes(currentListNode, previousListNode);
                }
                else
                {
                    printf("%d not more than %d\n", *currentValue, *previousValue);
                    correctPosition = TRUE;
                }
            }

            previousListNode = currentListNode->prev;
        }

        currentIndex += 1;
        printf("Index: %d\n", currentIndex);
        currentListNode = findIndex(dataList, currentIndex);
    }
}

void swapNodes(Node* currentNode, Node* prevNode)
{
    Node *tmpNode1, *tmpNode2;

    tmpNode1 = prevNode->prev;
    tmpNode2 = currentNode->next;

    currentNode->prev = tmpNode1;

    if (tmpNode1 != NULL)
    {
        tmpNode1->next = currentNode;
    }

    prevNode->next = tmpNode2;

    if (tmpNode2 != NULL)
    {
        tmpNode2->prev = prevNode;
    }

    prevNode->prev = currentNode;
    currentNode->next = prevNode;

}
