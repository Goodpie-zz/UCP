#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "csvparser.h"
#include "filereader.h"
#include "headerinfo.h"
#include "boolean.h"

#define MAX_HEADER_LENGTH 4096

static int parseHeaderLine(char*, LinkedList*);
static int validateHeader(char*, LinkedList*);
static int validateHeader(char*, LinkedList*);
static int validateType(char*);
static int parseDataLine(char*, LinkedList*, LinkedList*);
static int validateIntData(char*, LinkedList*);
static void validateStringData(char*, LinkedList*);

/**
 * SUBMODULE: parseCSV
 * IMPORT: FILE* inFile, LinkedList* dataList, LinkedList* headerList
 * EXPORT: int
 * Parses CSV file defined by assignment guidelines
 */
int parseCSV(FILE* inFile, LinkedList** outerDataList, LinkedList** headerList)
{
    int headerParseSuccess = TRUE, dataParseSuccess = TRUE;
    int endOfFile = FALSE;

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
    int success = TRUE;

    /* Tokenize line and validate each token */
    char* token = strtok(line, ",");
    while ((token != NULL) && (success == TRUE))
    {
        /* Validate and add to linked list */
        success = validateHeader(token, headerList);

        /* Next token */
        token = strtok(NULL, ",");
    }

    /* No longer need line, free it */
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

    int success = FALSE;
    int validType = TRUE;

    /* Allocate memory for headerInfo */
    headerInfo = (HeaderInfo*) malloc(sizeof(HeaderInfo));
    headerInfo->name = (char*) malloc(sizeof(char) * MAX_HEADER_LENGTH);
    headerInfo->type = (char*) malloc(sizeof(char) * MAX_HEADER_LENGTH);

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
                success = TRUE;
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
    /* Failed so free header */
    if (!success)
    {
        freeHeader(headerInfo);
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
    int valid = FALSE;

    /* Only valid options are integer and string */
    if ((strcmp(type, "string") == 0) || (strcmp(type, "integer") == 0))
        valid = TRUE;

    return valid;
}

/**
 * SUBMODULE: parseDataLine
 * IMPORT: char* line, LinkedList* outerDataList, LinkedList* headerList
 * EXPORT: int success
 * Validates the data line and adds it to out linked list
 */
 /* TODO: Shorten this function and increase cohesion */
int parseDataLine(char* line, LinkedList* outerDataList, LinkedList* headerList)
{
    int success = TRUE;

    LinkedList* dataList = createLinkedList();

    Node* currentHeader = headerList->head;
    HeaderInfo* headerInfo;

    char* token = strtok(line, ",");
    while (token != NULL && success == TRUE)
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
                success = FALSE;
            }

            /* Next token */
            token = strtok(NULL, ",");
        }
        else
        {
            /* More data than headers? */
            printf("Invalid CSV file format");
            success = FALSE;
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
    int success = FALSE;
    int* intValue;

    intValue = (int*) malloc(sizeof(int));
    if (sscanf(token, "%d", intValue) == 1)
    {
        insertLast(dataList, intValue);
        success = TRUE;
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
