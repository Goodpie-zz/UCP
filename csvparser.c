#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "csvparser.h"
#include "filereader.h"

LinkedList* parseCSV(FILE* inFile)
{
    int endOfFile = 0;
    char* line = NULL;
    LinkedList* linkedList = createLinkedList();
    while (!endOfFile)
    {
        line = readLine(inFile, &endOfFile);
        insertLast(linkedList, line);
        free(line);
    }

    return linkedList;
}

void defineHeaders(char* line, char** headers)
{

}










