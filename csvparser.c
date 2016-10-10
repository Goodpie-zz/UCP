#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "csvparser.h"
#include "filereader.h"

#define MAX_STRING_LENGTH 4096

/**
 * SUBMODULE: parseCSV
 * IMPORT: FILE*, LinkedList**, LinkedList**
 * EXPORT: int
 * Takes an infile and parses it into two seperate linked lists
 */
int parseCSV(FILE* inFile, LinkedList** dataList, LinkedList** headerList)
{
    /* vars for handling information about the CSV file */
    int currentLine = 1;
    int endOfFile = 0;
    int headerPass = 1;
    int linePass = 1;

    char* line = NULL;

    /* Create default linked lists for assigning values */
    *dataList = createLinkedList();
    *headerList = createLinkedList();

    /* Loop through file until error or EOF */
    while ((endOfFile == 0) && (headerPass == 1))
    {
        line = readLine(inFile, &endOfFile);
        if (currentLine == 1)
        {
            /* Header, insert into header list */
            headerPass = defineHeaders(line, *headerList);
        }
        else
        {
            /* Not header, insert into data list */
            linePass = parseLineToLinkedList(*dataList, *headerList, line);
        }
        currentLine += 1;
    }

    if (!headerPass)
    {
        freeLinkedList(*dataList);
        printf("Error: Failed to parse headers in CSV file\n");
    }

    if (!linePass)
    {
        if (currentLine < 3)
        {
            freeRowLinkedList(*dataList);
        }
        else
        {
            freeLinkedList(*dataList);
        }
    }

    return headerPass;
}

/**
 * SUBMODULE: defineHeaders
 * IMPORT: char*, LinkedList*
 * EXPORT: int
 * Reads a line containing headers and adds them to linked list
 */
int defineHeaders(char* line, LinkedList* headers)
{
    int success = 1;
    int headersAddded = 0;
    char* token;

    /* Tokenize the header line and get header definitions */
    token = strtok(line, ",");
    while (token != NULL && success == 1)
    {
        success = addHeaderFromToken(headers, token);

        /* Check if succeeded */
        if (!success)
        {
            if (headersAddded == 0)
            {
                /* Failed to add any header so free as LinkedList */
                freeLinkedList(headers);
            }
            else
            {
                /* Some headers have been added so call specialty free */
                freeHeaderLinkedList(headers);
            }
        }
        else
        {
            /* Added correctly so increment headers added */
            headersAddded += 1;
        }

        /* Continue tokenizing */
        token = strtok(NULL, ",");
    }

    free(line);
    return success;
}

/**
 * SUBMODULE: addHeaderFromToken
 * IMPORT: LinkedList*, char*
 * EXPORT: int
 * Adds a token representing a header to the linked list
 * Returns bool representing success
 */
int addHeaderFromToken(LinkedList* headers, char* token)
{
    int success = 1;
    HeaderInfo* header;

    /* Don't want to handle really long header names */
    if (strlen(token) > MAX_STRING_LENGTH)
    {
        printf("Header information to long\n");
        success = 0;
    }
    else
    {
        /* Can proceed with creating header information struct */
        header = (HeaderInfo*) malloc(sizeof(HeaderInfo));
        header->name = (char*) malloc(sizeof(char) * MAX_STRING_LENGTH);
        header->type = (char*) malloc(sizeof(char) * MAX_STRING_LENGTH);

         /* Check we are getting the correct amount of values from token */
        if (sscanf(token, "%s (%[^)])", header->name, header->type) == 2)
        {
            if (validateHeaderType(header->type))
            {
                /* Insert into headers list */
                insertLast(headers, header);
            }
            else
            {
                printf("Invalid header type defined: %s\n", header->type);
                freeHeader(header);
                success = 0;
            }
        }
        else
        {
            /* Invalid header parameters, free header and return fail */
            printf("Invalid header format: %s\n", token);
            freeHeader(header);
            success = 0;
        }
    }

    return success;
}

/**
 * SUBMODULE: validateHeaderType
 * IMPORT: char* EXPORT: int
 * Ensures that the header matches a valid type
 */
int validateHeaderType(char* type)
{
    int success = 0;

    /* Check for valid types */
    if (strcmp(type, "string") == 0)
    {
        success = 1;
    }
    else if (strcmp(type, "integer") == 0)
    {
        success = 1;
    }

    return success;
}

int parseLineToLinkedList(LinkedList* dataList, LinkedList* headerList, char* line)
{
    char* token;
    int tmpInteger;
    int success = 1;

    int headerIndex = 0;
    HeaderInfo* currentHeader;

    LinkedList* rowLinkedList = createLinkedList();

    /* Tokenize the header line and get header definitions */
    token = strtok(line, ",");
    while (token != NULL && success == 1)
    {
        currentHeader = (HeaderInfo*) findIndex(headerList, headerIndex);
        if (currentHeader != NULL)
        {
            if (strcmp(currentHeader->type, "string") == 0)
            {
                insertLast(rowLinkedList, token);
            }
            else if (strcmp(currentHeader->type, "integer") == 0)
            {
                if (sscanf(token, "%d", &tmpInteger) == 1)
                {
                    insertLast(rowLinkedList, &tmpInteger);
                }
                else
                {
                    success = 0;
                }
            }
        }
        else
        {
            success = 0;
        }

        /* Continue tokenizing */
        token = strtok(NULL, ",");

        headerIndex += 1;
    }

    insertLast(dataList, rowLinkedList);

    free(line);

    return success;
}

void freeRowLinkedList(LinkedList* linkedList)
{
    Node *outerNode, *outerNextNode;

    LinkedList* innerList;
    Node *innerNode, *innerNextNode;
    outerNode = linkedList->head;

    while (outerNode != NULL)
    {
        outerNextNode = outerNode->next;

        innerList = (LinkedList*) outerNode->value;
        innerNode = innerList->head;
        while (innerNode != NULL)
        {
            innerNextNode = innerNode->next;
            free(innerNode);
            innerNode = innerNextNode;
        }
        free(innerList);

        free(outerNode);
        outerNode = outerNextNode;
    }
    free(linkedList);
}

/**
 * SUBMODULE: freeHeaderLinkedList
 * IMPORT: LinkedList*
 * EXPORT: None
 * Handles specific case of freeing header list containing HeaderInfo struct
 */
void freeHeaderLinkedList(LinkedList* linkedList)
{
    HeaderInfo* value;
    Node *node, *nextNode;
    node = linkedList->head;

    /* Traverse list until last value (where next is NULL) */
    while (node != NULL)
    {
        /* Temporarily assign next node */
        nextNode = node->next;

        /* Cast value to HeaderInfo and free struct */
        value = (HeaderInfo*) node->value;
        freeHeader(value);
        free(node);

        node = nextNode;
    }

    /* Free LinkedList */
    free(linkedList);
}

/**
 * SUBMODULE: freeHeader
 * IMPORT: HeaderInfo* EXPORT: None
 * Handles freeing a HeaderInfo struct pointer
 */
void freeHeader(HeaderInfo* header)
{
    free(header->name);
    free(header->type);
    free(header);
}
