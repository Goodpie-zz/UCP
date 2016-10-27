/**
* FILE:          csvparser.c
* AUTHOR:        Brandyn Britton
* USERNAME:      18265716
* UNIT:          UCP
* PURPOSE:       UCP Assignment 2016 Semester 2
* COMMENTS:      handles the parsing of the CSV file in the format defined
*                by Assignment guidelines
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


#include "csvparser.h"
#include "filereader.h"
#include "headerinfo.h"
#include "boolean.h"

#define MAX_HEADER_LENGTH 4096

static int parseHeaderLine(char*, LinkedList*);
static int validateHeader(char*, LinkedList*, int);
static int validateType(char*);
static int parseDataLine(char*, LinkedList*, LinkedList*);
static int validateIntData(char*, LinkedList*);
static void validateStringData(char*, LinkedList*);
static int is_empty(const char*);

/**
 * SUBMODULE: parseCSV
 * IMPORT: inFile, dataList, headerList
 * EXPORT: success
 * Parses CSV file defined by assignment guidelines
 */
int parseCSV(FILE* inFile, LinkedList** outerDataList, LinkedList** headerList)
{
    int headerParseSuccess = TRUE, dataParseSuccess = TRUE;
    int success = FALSE;
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
            if (!is_empty(line))
            {
                printf("meme\n");
                dataParseSuccess = parseDataLine(line, *outerDataList, *headerList);
            }
            free(line);
        }

        if (!dataParseSuccess)
        {
            /* Failed. pritn out error and free data */
            printf("Failed to read in CSV file due to invalid data format\n");
            freeHeaderLinkedList(*headerList);
            freeOuterLinkedList(*outerDataList);
        }
    }
    else
    {
        /* Failed to read header information so print out error and free data */
        printf("Invalid row headers defined in CSV file\n");
        freeHeaderLinkedList(*headerList);
        freeOuterLinkedList(*outerDataList);
    }

    success = headerParseSuccess && dataParseSuccess;
    return success;
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
    int index = 0;
    char* token;

    /* Ensure string isn't empty */
    if (strlen(line) != 0)
    {
        /* Tokenize line and validate each token */
        token = strtok(line, ",");
        while ((token != NULL) && (success == TRUE))
        {
            /* Validate and add to linked list */
            success = validateHeader(token, headerList, index);
            index += 1;

            /* Next token */
            token = strtok(NULL, ",");
        }
    }

    /* No longer need line, free it */
    free(line);

    if (linkedListIsEmpty(headerList))
    {
        success = FALSE;
    }

    return success;
}

/**
 * SUBMODULE: validateHeader
 * IMPORT: char* token, LinkedList* headerList
 * EXPORT: int success
 * Ensures the header is valid and adds it to linked list if true
 */
int validateHeader(char* token, LinkedList* headerList, int index)
{
    HeaderInfo* headerInfo;

    int success = FALSE;
    int validType = TRUE;

    printf("Inside header: Index = %d\n", index);

    /* Allocate memory for headerInfo */
    headerInfo = (HeaderInfo*) malloc(sizeof(HeaderInfo));
    headerInfo->name = (char*) malloc(sizeof(char) * MAX_HEADER_LENGTH);
    headerInfo->type = (char*) malloc(sizeof(char) * MAX_HEADER_LENGTH);
    headerInfo->index = index;

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
 /* TODO: Shorten this function */
int parseDataLine(char* line, LinkedList* outerDataList, LinkedList* headerList)
{
    int success = TRUE;

    int dataCount = 0;

    LinkedList* innerList = createLinkedList();

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
                validateStringData(token, innerList);
            }
            else if (strcmp(headerInfo->type, "integer") == 0)
            {
                /* Ensure the int data can be converted nicely */
                /* Check type of string or empty int */
                if (strcmp(token, " ") == 0)
                {
                    insertLast(innerList, NULL);
                }
                else
                {
                    success = validateIntData(token, innerList);
                }
            }
            else
            {
                printf("Cannot convert %s to %s", token, headerInfo->type);
                success = FALSE;
            }

            dataCount += 1;
            currentHeader = currentHeader->next;

            /* Next token */
            token = strtok(NULL, ",");
        }
        else
        {
            /* More data than headers? */
            printf("Invalid CSV file format");
            success = FALSE;
        }

    }



    if (success)
    {
        if (dataCount != headerList->size)
        {
            printf("Invalid amount of columns in CSV file\n");
            success = FALSE;
        }
        else
        {
            insertLast(outerDataList, innerList);
        }
    }
    else
    {
        freeLinkedList(innerList);
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

    /* Allocate memory to int for handling freeing of linked list */
    intValue = (int*) malloc(sizeof(int));

    /* Check that token contains int value */
    if (sscanf(token, "%d", intValue) == 1)
    {
        /* Insert int into linkedList */
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

int is_empty(const char *s) {
  while (*s != '\0') {
    if (!isspace(*s))
      return 0;
    s++;
  }
  return 1;
}

/*
 * SUBMODULE: freeOuterLinkedList
 * IMPORT: linkedList
 * EXPORT: None
 * Frees linked list of linked lists
 */
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
