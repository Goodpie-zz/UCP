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

static int sortByInt(int*, int*, int);
static int sortByString(char*, char*, int);

/**
 * SUBMODULE: sortList
 * IMPORT: dataList, header, order
 * EXPORT: None
 * Sorts list using user parameters
 */
void sortList(LinkedList* dataList, HeaderInfo* header, int order)
{
    int i, j;
    int posFound;
    LinkedList *curList, *prevList;
    void *curValue, *prevValue;

    int index = header->index;
    printf("datalist->size = %d\n", dataList->size);
    /* Loop through outer list and get all inner nodes */
    for (i = 1; i < dataList->size; i++)
    {
        posFound = FALSE;
        j =  i;
        /* Compare current node with previous node if it exists */
        while ((j > 0) && (!posFound))
        {
            printf("j = %d\n", j);
            /* Get list values from the nodes */
            curList = (LinkedList*) findIndex(dataList, j);
            prevList = (LinkedList*) findIndex(dataList, j - 1);

            /* Get void* values from the lists */
            curValue = findIndex(curList, index);
            prevValue = findIndex(prevList, index);

            if (strcmp(header->type, "integer") == 0)
            {
                printf("Sorting by int \n");
                /* Values are ints so compare */
                posFound = sortByInt((int*) curValue, (int*) prevValue, order);
            }
            else
            {
                printf("Sorting by string \n");
                /* Values are strings so compare */
                posFound = sortByString((char*) curValue, (char*) prevValue, order);
            }

            if (!posFound)
            {
                /* Swap nodes as incorrect position */
                swapNodesByIndex(dataList, j, j - 1);
            }

            j -= 1;

        }
    }
}

/**
 * SUBMODULE: sortByInt
 * IMPORT: current, prev, order
 * EXPORT: posFound
 * Compares two ints and ensures that they are in the
 * currect position
 */
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

/**
 * SUBMODULE: sortByString
 * IMPORT: current, prev, order
 * EXPORT: posFound
 * Compares two strings and ensures that they are in the
 * currect position
 */
int sortByString(char* current, char* prev, int order)
{

    int posFound = TRUE;
    printf("Sorting by string \n");
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
