/**
* FILE:         insertionsort.c
* AUTHOR:       Brandyn Britton
* USERNAME:     18265716
* UNIT:         UCP
* PURPOSE:      UCP Assignment 2016 Semester 2
* COMMENTS:     Handles the insertion sort of the csv file data
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "headerinfo.h"
#include "insertionsort.h"
#include "boolean.h"

static int checkPositionFound(int, int);

/**
 * SUBMODULE: sortList
 * IMPORT: dataList, header, order
 * EXPORT: None
 * Sorts list using user parameters
 */
void sortList(LinkedList* dataList, int index, int order, int (*compare)(void*, void*))
{
    int i, j;
    int posFound;
    int isLarger;
    LinkedList *curList, *prevList;
    void *curValue, *prevValue;

    printf("index = %d\n", index);
    /* Loop through outer list and get all inner nodes */
    for (i = 1; i < dataList->size; i++)
    {
        posFound = FALSE;
        j =  i;
        /* Compare current node with previous node if it exists */
        while ((j > 0) && (!posFound))
        {
            /* Get list values from the nodes */
            curList = (LinkedList*) findIndex(dataList, j);
            prevList = (LinkedList*) findIndex(dataList, j - 1);

            /* Get void* values from the lists */
            curValue = findIndex(curList, index);
            prevValue = findIndex(prevList, index);

            isLarger = compare(curValue, prevValue);

            posFound = checkPositionFound(isLarger, order);
            printf("posFound = %d\n", posFound);

            if (posFound == FALSE)
            {
                /* Swap nodes as incorrect position */
                swapNodesByIndex(dataList, j, j - 1);
            }

            j -= 1;

        }
    }
}

int checkPositionFound(int isLarger, int order)
{
    int positionFound = FALSE;
    if (order == ASCENDING)
    {
        if (isLarger == FALSE)
        {
            positionFound = TRUE;
        }
    }
    else if (order == DESCENDING)
    {
        if (isLarger == TRUE)
        {
            positionFound = TRUE;
        }
    }

    return positionFound;
}

int compareInt(void* current, void* previous)
{
    int *curValue = NULL, *prevValue = NULL;
    int isLarger = FALSE;

    curValue = (int*) current;
    prevValue = (int*) previous;

    if (prevValue == NULL)
    {
        /* NULL < NOT NULL */
        if (curValue != NULL)
        {
            isLarger = TRUE;
        }
    }
    else
    {
        if (curValue != NULL)
        {
            /* Compare two int values */
            isLarger = (*curValue > *prevValue);
        }
    }

    return isLarger;
}

int compareString(void* current, void* previous)
{
    char *curValue= NULL, *prevValue = NULL;
    int isLarger = FALSE;

    curValue = (char*) current;
    prevValue = (char*) previous;

    if (prevValue == NULL)
    {
        /* NULL < NOT NULL */
        if (curValue != NULL)
        {
            printf("NOT NULL > NULL\n");
            isLarger = TRUE;
        }
    }
    else
    {
        if (curValue != NULL)
        {
            printf("%s > %s = ", curValue, prevValue);
            /* Compare two int values */
            isLarger = strcmp(curValue, prevValue) > 0;

        }
    }

    printf("%d\n", isLarger);

    return isLarger;
}
