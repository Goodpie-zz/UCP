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

            /* Check if current is larger than previous */
            isLarger = compare(curValue, prevValue);

            /* Check if in correct position */
            posFound = checkPositionFound(isLarger, order);

            if (posFound == FALSE)
            {
                /* Swap nodes as incorrect position */
                swapNodesByIndex(dataList, j, j - 1);
            }

            j -= 1;

        }
    }
}

/**
 * SUBMODULE: checkPositionFound
 * IMPORT: isLarger, order
 * EXPORT: isLarger
 * Checks if the two items are in the correct position 
 */
int checkPositionFound(int isLarger, int order)
{
    int positionFound = FALSE;

    if (order == DESCENDING)
    {
        /* Order large -> small */
        if (isLarger == FALSE)
        {
            /* Values in correct position */
            positionFound = TRUE;
        }
    }
    else if (order == ASCENDING)
    {
        /* Order small -> large */
        if (isLarger == TRUE)
        {
            /* Values in correct position */
            positionFound = TRUE;
        }
    }

    return positionFound;
}
 
/**
 * SUBMODULE: compareInt
 * IMPORT: currnet, previous
 * EXPORT: isLarger
 * Compares two integers and checks if current is larger than previous
 */
int compareInt(void* current, void* previous)
{
    int *curValue = NULL, *prevValue = NULL;
    int isLarger = FALSE;

    /* Extract values from NULL pointer */
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

/**
 * SUBMODULE: compareString
 * IMPORT: current, previous
 * EXPORT: isLarger
 * Comapres two sets of strings and check which is larger
 */
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
            isLarger = TRUE;
        }
    }
    else
    {
        if (curValue != NULL)
        {
            /* Compare two int values */
            isLarger = strcmp(curValue, prevValue) > 0;

        }
    }

    return isLarger;
}
