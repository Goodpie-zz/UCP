/**
* FILE:         csvparser.h
* AUTHOR:       Brandyn Britton
* USERNAME:     18265716
* UNIT:         UCP
* PURPOSE:      UCP Assignment 2016 Semester 2
* COMMENTS:     Headerfile for csvparser.c
*/

#ifndef LINKEDLIST_H
    #define LINKEDLIST_H
    #include "linkedlist.h"
#endif

/**
 * SUBMODULE: parseCSV
 * IMPORT: FILE*, LinkedList**, LinkedList**
 * EXPORT: int
 * Parses CSV file defined by assignment guidelines
 */
int parseCSV(FILE*, LinkedList**, LinkedList**);

/*
 * SUBMODULE: freeOuterLinkedList
 * IMPORT: LinkedList*
 * EXPORT: None
 * Frees linked list of linked lists
 */
void freeOuterLinkedList(LinkedList*);
