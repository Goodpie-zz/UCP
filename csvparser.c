#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "csvparser.h"
#include "filereader.h"

LinkedList* parseCSV(FILE* inFile)
{
    int currentLine = 1;
    int endOfFile = 0;
    int headerPass = 1;

    char* line = NULL;
    LinkedList* data = createLinkedList();
    LinkedList* headers = createLinkedList();

    while ((endOfFile == 0) && (headerPass == 1))
    {
        line = readLine(inFile, &endOfFile);
        if (currentLine == 1)
        {
            printf("%s\n", line);
            headerPass = defineHeaders(line, &headers);
        }

        insertLast(data, line);
        currentLine += 1;
        free(line);
    }

    if (!headerPass)
    {
        printf("exiting program due to invalid column headers\n");
    }

    freeHeaderLinkedList(headers);
    return data;
}

int defineHeaders(char* line, LinkedList** headers)
{
    int success = 1;
    HeaderInfo* header = (HeaderInfo*) malloc(sizeof(HeaderInfo));

    char* token = strtok(line, ",");
    char tmpType[4096];
    char tmpName[4096];

    while (token != NULL && success == 1)
    {
        if (strlen(token) > 4096)
        {
            printf("Header information to long");
            success = 0;
        }
        else
        {
            if (sscanf(token, "%s (%[^)])", tmpName, tmpType) == 2)
            {
                printf("%s %s\n", tmpName, tmpType);

                /* Determine what type of data it is */
                header->name = (char*) malloc(sizeof(char) * strlen(tmpName));
                strcpy(header->name, tmpName);
                header->type = (char*) malloc(sizeof(char) * 7);
                determineHeaderType(tmpType, header->type);

                if (strcmp(header->type, "NA") == 0)
                {
                    printf("Invalid column header data type: %s\n", tmpType);
                    success = 0;
                }
                else
                {
                    printf("Inserting: %s of type %s\n", header->name, header->type);
                    insertLast(*headers, header);
                }
                free(header->name);
                free(header->type);
            }
            else
            {
                printf("Invalid column header forma %s\n", token);
                success = 0;
            }
        }
        token = strtok(NULL, ",");
    }

    free(header);

    return success;
}

void determineHeaderType(char* title, char* type)
{
    if (strcmp(title, "integer") == 0)
    {
        strcpy(type,"int\0");
    }
    else if (strcmp(title, "string") == 0)
    {
        strcpy(type,"string\0");
    }
    else if (strcmp(title, "float") == 0)
    {
        strcpy(type,"float\0");
    }
    else if (strcmp(title, "double") == 0)
    {
        strcpy(type,"double\0");
    }
    else
    {
        strcpy(type,"NA\0");
    }

}

void freeHeaderLinkedList(LinkedList* headerLinkedList)
{
    Node* tmp;
    Node* currentNode = headerLinkedList->tail;
    HeaderInfo* headerInfo;

    while (currentNode->prev != NULL)
    {
        tmp = currentNode;
        headerInfo = (HeaderInfo*) tmp->value;
        freeHeaderInfo(headerInfo);
        currentNode = tmp->prev;
        free(tmp);
    }

    free(currentNode);
    free(headerLinkedList);
}


void freeHeaderInfo(HeaderInfo* HeaderInfo)
{
    free(HeaderInfo->name);
    free(HeaderInfo->type);
    free(HeaderInfo);
}
