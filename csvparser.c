#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "csvparser.h"
#include "filereader.h"

#define MAX_HEADER_LENGTH 4096

/**
 * SUBMODULE: parseCSV
 * IMPORT: FILE* inFile, LinkedList* dataList, LinkedList* headerList
 * EXPORT: int
 * Parses CSV file defined by assignment guidelines
 */
int parseCSV(FILE* inFile, LinkedList** outerDataList, LinkedList** headerList)
{
    int headerParseSuccess = 1, dataParseSuccess = 1;
    int endOfFile = 0;

    char* line = NULL;

    /* Initiate linked lists */
    *outerDataList = createLinkedList();
    *headerList = createLinkedList();

    /* First parse header information */
    line = readLine(inFile, &endOfFile);
    headerParseSuccess = parseHeaderLine(line, *headerList);

    /* Loop through rest of file to parse each line */
    if (headerParseSuccess)
    {
        while ((!endOfFile) && (dataParseSuccess))
        {
            line = readLine(inFile, &endOfFile);
            dataParseSuccess = parseDataLine(line, *outerDataList, *headerList);
        }

        if (!dataParseSuccess)
        {
            printf("Failed to read in data from CSV file. Invalid format\n");
            freeHeaderLinkedList(*headerList);
            freeOuterLinkedList(*outerDataList);
        }
    }
    else
    {
        printf("Failed to read header file\n");
        freeHeaderLinkedList(*headerList);
        freeOuterLinkedList(*outerDataList);
    }

    return headerParseSuccess && dataParseSuccess;

}

/**
 * SUBMODULE: parseHeaderLine
 * IMPORT: char* line, LinkedList* headerList
 * EXPORT: None
 * Loops through header for header tokens and adds to headerList
 */
int parseHeaderLine(char* line, LinkedList* headerList)
{
    int success = 1;

    /* Tokenize line and validate each token */
    char* token = strtok(line, ",");
    while ((token != NULL) && (success == 1))
    {
        /* Validate and add to linked list */
        success = validateHeader(token, headerList);

        /* Next token */
        token = strtok(NULL, ",");
    }

    free(line);

    return success;
}

/**
 * SUBMODULE: validateHeader
 * IMPORT: char* token, LinkedList* headerList
 * EXPORT: int success
 * Ensures the header is valid and adds it to linked list if true
 */
int validateHeader(char* token, LinkedList* headerList)
{
    HeaderInfo* headerInfo;

    int success = 0;
    int validType;

    headerInfo = (HeaderInfo*) malloc(sizeof(HeaderInfo));
    headerInfo->name = malloc(sizeof(char) * MAX_HEADER_LENGTH);
    headerInfo->type = malloc(sizeof(char) * MAX_HEADER_LENGTH);

    if (strlen(token) < (MAX_HEADER_LENGTH * 2))
    {
        /* String split into <name> (<type>) */
        if (sscanf(token, "%s (%[^)])",
            headerInfo->name, headerInfo->type) == 2)
        {
            validType = validateType(headerInfo->type);
            if (validType)
            {
                /* Insert into the last element of linked list */
                insertLast(headerList, headerInfo);
                success = 1;
            }
            else
            {
                printf("Invalid header type: %s\n", headerInfo->type);
            }
        }
        else
        {
            printf("Invalid header item: %s\n",  token);
        }
    }

    if (!success)
    {
        free(headerInfo->name);
        free(headerInfo->type);
        free(headerInfo);
    }

    return success;
}

/**
 * SUBMODULE: validateType
 * IMPORT: char* type
 * EXPORT: int valid
 * Validates the header type to ensure it is string or integer
 */
int validateType(char* type)
{
    int valid = 0;

    /* Only valid options are integer and string */
    if ((strcmp(type, "string") == 0) || (strcmp(type, "integer") == 0))
        valid = 1;

    return valid;
}

/**
 * SUBMODULE: parseDataLine
 * IMPORT: char* line, LinkedList* outerDataList, LinkedList* headerList
 * EXPORT: int success
 * Validates the data line and adds it to out linked list
 */
int parseDataLine(char* line, LinkedList* outerDataList, LinkedList* headerList)
{
    int success = 1;

    LinkedList* dataList = createLinkedList();

    Node* currentHeader = headerList->head;
    HeaderInfo* headerInfo;

    char* token = strtok(line, ",");
    while (token != NULL && success == 1)
    {
        /* Ensure the node isn't null */
        if (currentHeader != NULL)
        {
            /* Get the current header type for validation */
            headerInfo = (HeaderInfo*) currentHeader->value;

            
            if (strcmp(headerInfo->type, "string") == 0)
            {
                /* String is already valid, just copy string */
                validateStringData(token, dataList);
            }
            else if (strcmp(headerInfo->type, "integer") == 0)
            {
                /* Ensure the int data can be converted nicely */
                /* Check type of string or empty int */
                if (strcmp(token, " ") == 0)
                {
                    insertLast(dataList, NULL);
                }
                else
                {
                    success = validateIntData(token, dataList);
                }
            }
            else
            {
                printf("Cannot convert %s to %s", token, headerInfo->type);
                success = 0;
            }

            /* Next token */
            token = strtok(NULL, ",");
        }
        else
        {
            /* More data than headers? */
            printf("Invalid CSV file format");
            success = 0;
        }

        currentHeader = currentHeader->next;

    }

    free(line);

    if (success)
    {
        insertLast(outerDataList, dataList);
    }
    else
    {
        freeLinkedList(dataList);
    }

    return success;

}

/**
 * SUBMODULE: validateIntData
 * IMPORT: char* token, LinkedList* dataList
 * EXPORT: int success
 * Ensures the int provided can be nicely converted to int
 */
int validateIntData(char* token, LinkedList* dataList)
{
    int success = 0;
    int* intValue;

    intValue = (int*) malloc(sizeof(int));
    if (sscanf(token, "%d", intValue) == 1)
    {
        insertLast(dataList, intValue);
        success = 1;
    }
    else
    {
        free(intValue);
    }

    return success;
}

/**
 * SUBMODULE: validateStringData
 * IMPORT: char* token, LinkedList* dataList
 * EXPORT: None
 * Copies the string to a memory allocation and adds it to linked list
 */
void validateStringData(char* token, LinkedList* dataList)
{
    char* strValue;

    /* Allocate memory for value in linked list */
    strValue = (char*) malloc(sizeof(char) * strlen(token) + 1);

    /* Copy string */
    strcpy(strValue, token);

    /* Insert into the last element of the linked list */
    insertLast(dataList, strValue);
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

    if (linkedListIsEmpty(linkedList))
    {
        freeLinkedList(linkedList);
    }
    else
    {
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


void freeOuterLinkedList(LinkedList* linkedList)
{
    Node *outerNode, *outerNextNode;
    LinkedList* innerList;

    if (linkedListIsEmpty(linkedList))
    {
        freeLinkedList(linkedList);
    }
    else
    {
        Node *innerNode, *innerNextNode;
        outerNode = linkedList->head;

        while (outerNode != NULL)
        {
            outerNextNode = outerNode->next;

            innerList = (LinkedList*) outerNode->value;

            freeLinkedList(innerList);
            free(outerNode);

            outerNode = outerNextNode;
        }
        free(linkedList);
    }
}
