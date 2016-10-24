#ifndef LINKEDLIST_H
    #define LINKEDLIST_H
    #include "linkedlist.h"
#endif

typedef struct
{
    char* name;
    char* type;
    int index;
} HeaderInfo;

void freeHeaderLinkedList(LinkedList*);
void freeHeader(HeaderInfo*);
