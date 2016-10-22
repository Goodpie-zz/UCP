#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "headerinfo.h"
#include "insertionsort.h"
#include "boolean.h"

static int compareIntVal(Node*, Node*, int, int);
static int compareCharVal(Node*, Node*, int, int);
static char* getCharVal(LinkedList*, int);
static int* getIntVal(LinkedList*, int);
static LinkedList* getLinkedList(Node*);


void sortList(int headerIndex, HeaderInfo* header, LinkedList* dataList, int order)
{
    int posFound = FALSE;
    int currentIndex = 0;

    Node *curOuterNode, *prevOuterNode;

    curOuterNode = dataList->head;

    while (curOuterNode != NULL)
    {

        posFound = FALSE;
        prevOuterNode = curOuterNode->prev;

        while ((!posFound) && (prevOuterNode != NULL))
        {
            if (strcmp(header->type, "string") == 0)
            {
                posFound = compareCharVal(curOuterNode, prevOuterNode,
                    headerIndex, order);
            }
            else if (strcmp(header->type, "integer") == 0)
            {
                posFound = compareIntVal(curOuterNode, prevOuterNode,
                    headerIndex, order);
            }

            if (!posFound)
            {
                swapNodes(curOuterNode, prevOuterNode);
            }
        }

        currentIndex += 1;
        curOuterNode = findIndex(dataList, currentIndex);
    }
}

int compareIntVal(Node* curOuterNode, Node* prevOuterNode, int index, int order)
{
    LinkedList *curList, *prevList;
    int *curVal, *prevVal;
    int posFound = TRUE;

    curList = getLinkedList(curOuterNode);
    prevList = getLinkedList(prevOuterNode);

    curVal = getIntVal(curList, index);
    prevVal = getIntVal(prevList, index);

    if (order == ASCENDING)
    {
        if ((curVal == NULL) || (prevVal == NULL))
        {
            if ((curVal == NULL) && (prevVal != NULL))
            {
                posFound = FALSE;
            }
        }
        else if (*curVal < *prevVal)
        {
            posFound = FALSE;
        }
    }
    else if (order == DESCENDING)
    {
        if ((curVal == NULL) || (prevVal == NULL))
        {
            if ((curVal != NULL) && (prevVal == NULL))
            {
                posFound = FALSE;
            }
        }
        else if (*curVal > *prevVal)
        {
            posFound = FALSE;
        }
    }

    return posFound;
}

int compareCharVal(Node* curOuterNode, Node* prevOuterNode, int index, int order)
{
    LinkedList *curList, *prevList;
    char *curVal, *prevVal;
    int posFound = TRUE;

    curList = getLinkedList(curOuterNode);
    prevList = getLinkedList(prevOuterNode);

    curVal = getCharVal(curList, index);
    prevVal = getCharVal(prevList, index);

    if (order == ASCENDING)
    {
        if ((curVal == NULL) || (prevVal == NULL))
        {
            if ((curVal == NULL) && (prevVal != NULL))
            {
                posFound = FALSE;
            }
        }
        else if (curVal < prevVal)
        {
            posFound = FALSE;
        }
    }
    else if (order == DESCENDING)
    {
        if ((curVal == NULL) || (prevVal == NULL))
        {
            if ((curVal != NULL) && (prevVal == NULL))
            {
                posFound = FALSE;
            }
        }
        else if (curVal > prevVal)
        {
            posFound = FALSE;
        }
    }

    return posFound;
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

int* getIntVal(LinkedList* list, int index)
{
    int* value = NULL;
    Node* node = findIndex(list, index);
    if (node != NULL)
    {
        value = (int*) node->value;
    }

    return value;
}

char* getCharVal(LinkedList* list, int index)
{
    char* value = NULL;
    Node* node = findIndex(list, index);
    if (node != NULL)
    {
        value = (char*) node->value;
    }

    return value;
}
