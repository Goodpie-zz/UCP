#ifndef LINKEDLIST_H
    #define LINKEDLIST_H
    #include "linkedlist.h"
#endif

typedef struct
{
    char* type;
    char* name;
} HeaderInfo;

int parseCSV(FILE*, LinkedList**, LinkedList**);

void freeCSVLinkedList(LinkedList*);

int defineHeaders(char*, LinkedList*);
char* determineHeaderType(char*);

void freeHeaderLinkedList(LinkedList*);
void freeHeaderInfo(HeaderInfo*);
