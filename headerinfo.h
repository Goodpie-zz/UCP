/**
* FILE:         headerinfo.h
* AUTHOR:       Brandyn Britton
* USERNAME:     18265716
* UNIT:         UCP
* PURPOSE:      UCP Assignment 2016 Semester 2
* COMMENTS:     Header file for headerinfo.c
*/

#ifndef LINKEDLIST_H
    #define LINKEDLIST_H
    #include "linkedlist.h"
#endif

/* Define struct to handle header information */
typedef struct
{
    char* name;
    char* type;
    int index;
} HeaderInfo;

/**
 * SUBMODULE: freeHeaderLinkedList
 * IMPORT: LinkedList*
 * EXPORT: None
 * Handles specific case of freeing header list containing HeaderInfo struct
 */
void freeHeaderLinkedList(LinkedList*);

/**
 * SUBMODULE: freeHeader
 * IMPORT: HeaderInfo* 
 * EXPORT: None
 * Handles freeing a HeaderInfo struct pointer
 */
void freeHeader(HeaderInfo*);
