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

int parseHeaderLine(char*, LinkedList*);

int validateHeader(char*, LinkedList*);

int validateType(char*);

int parseDataLine(char*, LinkedList*, LinkedList*);

int validateIntData(char* token, LinkedList*);

void validateStringData(char*, LinkedList*);

void freeHeaderLinkedList(LinkedList*);

void freeHeader(HeaderInfo*);

void freeOuterLinkedList(LinkedList*);
