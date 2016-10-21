#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "headerinfo.h"
#include "insertionsort.h"
#include "boolean.h"

static void sortByString(int, LinkedList*, int);
static void sortByInteger(int, LinkedList*, int);
static void swapNodes(Node*, Node*);
static LinkedList* getLinkedList(Node*);
static int getIntValue(LinkedList*, int);

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

/* TODO: Handle null value comparison */
void sortByInteger(int headerIndex, LinkedList* dataList, int order)
{
    int currentIndex = 0;
    int posFound;
    LinkedList *currentList, *previousList;
    Node *currentNode, *previousNode;
    int currentValue, previousValue;

    currentNode = dataList->head;
    while (currentNode != NULL)
    {
        previousNode = currentNode->prev;
        posFound = FALSE;
        while ((previousNode != NULL) && (posFound == FALSE))
        {
            currentList = getLinkedList(currentNode);
            previousList = getLinkedList(previousNode);

            currentValue = getIntValue(currentList, headerIndex);
            previousValue = getIntValue(previousList, headerIndex);

            if (order == ASCENDING)
            {
                if (currentValue < previousValue)
                {
                    swapNodes(currentNode, previousNode);
                }
                else
                {
                    posFound = TRUE;
                }
            }
            else if (order == DESCENDING)
            {
                if (currentValue > previousValue)
                {
                    swapNodes(currentNode, previousNode);
                }
                else
                {
                    posFound = TRUE;
                }
            }
        }

        currentIndex += 1;
        currentNode = findIndex(dataList, currentIndex);
    }
}

LinkedList* getLinkedList(Node* node)
{
    LinkedList* value = NULL;
    if (node != NULL)
    {
        value = (LinkedList*) node->value;
    }
    return value;
}

int getIntValue(LinkedList* list, int index)
{
    int returnValue;
    Node* node = findIndex(list, index);
    if (node != NULL)
    {
        returnValue = *((int*) node->value);
    }

    return returnValue;
}

void swapNodes(Node* currentNode, Node* prevNode)
{
    void* tmp = currentNode->value;
    currentNode->value = prevNode->value;
    prevNode->value = tmp;

}
