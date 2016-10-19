#ifndef LINKEDLIST_H
    #define LINKEDLIST_H
    #include "linkedlist.h"
#endif

typedef struct
{
    char* type;
    char* name;
} HeaderInfo;

void freeHeaderLinkedList(LinkedList*);
void freeHeader(HeaderInfo*);
