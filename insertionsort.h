/**
* FILE:         insertionsort.h
* AUTHOR:       Brandyn Britton
* USERNAME:     18265716
* UNIT:         UCP
* PURPOSE:      UCP Assignment 2016 Semester 2
* COMMENTS:     Headerfile for insertionsort.c
*/

#ifndef LINKEDLIST_H
    #define LINKEDLIST_H
    #include "linkedlist.h"
#endif

/* Define values for ascending and descending */
#define ASCENDING 0
#define DESCENDING 1

/**
 * SUBMODULE: sortList
 * IMPORT: LinkedList*, HeaderInfo*, in
 * EXPORT: None
 * Sorts list using user parameters 
 */
void sortList(LinkedList*, int, int, int (*compare)(void*, void*));

int compareString(void*, void*);

int compareInt(void*, void*);