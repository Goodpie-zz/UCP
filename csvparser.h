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
