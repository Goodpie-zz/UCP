#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "headerinfo.h"
#include "insertionsort.h"
#include "boolean.h"

static int sortByInt(int*, int*, int);
int sortByString(char*, char*, int);

void sortList(LinkedList* dataList, HeaderInfo* header, int order)
{
    int i, j;
    int posFound;
    LinkedList *curList, *prevList;
    void *curValue, *prevValue;

    int index = header->index;

    for (i = 1; i < dataList->size - 1; i++)
    {
        posFound = FALSE;
        j =  i;
        while ((j > 0) && (!posFound))
        {
            curList = (LinkedList*) findIndex(dataList, j);
            prevList = (LinkedList*) findIndex(dataList, j - 1);

            curValue = findIndex(curList, index);
            prevValue = findIndex(prevList, index);

            if (strcmp(header->type, "integer") == 0)
            {
                posFound = sortByInt((int*) curValue, (int*) prevValue, order);
            }
            else
            {
                posFound = sortByString((char*) curValue, (char*) prevValue, order);
            }

            if (!posFound)
            {
                swapNodesByIndex(dataList, j, j - 1);
            }

            j --;

        }
    }
}

int sortByInt(int* current, int* prev, int order)
{
    int posFound = TRUE;
    if (order == ASCENDING)
    {
        if (current == NULL)
        {
            posFound = FALSE;
        }
        else if (prev != NULL)
        {
            if (*current < *prev)
            {
                posFound = FALSE;
            }
        }
    }
    else
    {
        if (prev == NULL)
        {
            posFound = FALSE;
        }
        else if (current != NULL)
        {
            if (*current > *prev)
            {
                posFound = FALSE;
            }
        }
    }

    return posFound;
}

int sortByString(char* current, char* prev, int order)
{
    int posFound = TRUE;
    if (order == ASCENDING)
    {
        if (current == NULL)
        {
            posFound = FALSE;
        }
        else if (prev != NULL)
        {
            if (strcmp(current, prev) < 0)
            {
                posFound = FALSE;
            }
        }
    }
    else
    {
        if (prev == NULL)
        {
            posFound = FALSE;
        }
        else if (current != NULL)
        {
            if (strcmp(current, prev) > 0)
            {
                posFound = FALSE;
            }
        }
    }

    return posFound;
}
