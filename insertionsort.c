#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "headerinfo.h"
#include "insertionsort.h"
#include "boolean.h"

static int sortByInt(int*, int*, int);

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
                printf("\nComparing at i = %d, j = %d\n", j, j - 1);
                posFound = sortByInt((int*) curValue, (int*) prevValue, order);
            }

            if (!posFound)
            {
                printf("Swapping\n");
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

    }
    else
    {
        if (prev == NULL)
        {
            printf("prev = NULL\n");
            posFound = FALSE;
        }
        else if (current != NULL)
        {
            printf("Comparing %d with %d\n", *current, *prev);
            if (*current > *prev)
            {
                posFound = FALSE;
            }
        }
    }

    return posFound;
}
