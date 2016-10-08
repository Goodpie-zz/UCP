#ifndef LINKEDLIST_H
    #define LINKEDLIST_H
    #include "linkedlist.h"
#endif

typedef struct
{
    char* type;
    char* name;
} HeaderInfo;

LinkedList* parseCSV(FILE*);

void freeCSVLinkedList(LinkedList*);

int defineHeaders(char*, LinkedList**);
void determineHeaderType(char*, char*);

void freeHeaderLinkedList(LinkedList*);
void freeHeaderInfo(HeaderInfo*);
