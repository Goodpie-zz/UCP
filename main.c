 /**
 * FILE:        main.c
 * AUTHOR:      Brandyn Britton
 * USERNAME:    18265716
 * UNIT:        UCP
 * PURPOSE:
 * COMMENTS:
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "csvparser.h"
#include "filereader.h"

/* Assuming file name can only have a max of 255 chars */
#define MAX_FILENAME_SIZE 255

void displayOuterList(LinkedList*, LinkedList*);

/**
 * SUBMODULE: main
 * IMPORT: argc, argv[]
 * EXPORT: int
 * Controls the main flow of the program
 */
int main(int argc, char* argv[])
{
    FILE *inFile, *outFile;
    int validInFile, validOutFile;
    char inFileName[MAX_FILENAME_SIZE], outFileName[MAX_FILENAME_SIZE];

    LinkedList* dataList = NULL;
    LinkedList* headerList = NULL;

    if (validateArguments(argc, argv, inFileName, outFileName))
    {
        /* Arguments validates */
        /* Check IO files for errors */
        validInFile = openFile(&inFile, inFileName, "r");
        validOutFile = openFile(&outFile, outFileName, "w");

        if (validInFile && validOutFile)
        {
            if (parseCSV(inFile, &dataList, &headerList))
            {
                displayOuterList(headerList, dataList);
                freeOuterLinkedList(dataList);
                freeHeaderLinkedList(headerList);
            }
            else
            {
                printf("Exiting: invalid CSV file\n");
            }

            fclose(inFile);
            fclose(outFile);
        }
        else
        {
            /* fileinvalid so close based on which one failed */
            if (!validInFile)
            {
                fclose(outFile);
            }
            else if (!validOutFile)
            {
                fclose(inFile);
            }
        }
    }
    else
    {
        /* Show user how to use program */
        usage("Invalid arguments provided");
    }

    return 0;
}

/**
 * SUBMODULE: validateAguments
 * IMPORT: argc, argv, inFileName, outFileName
 * EXPORT: (int) boolean
 * Checks whether the arguments provided by the user are valid and also
 *      determines the correct file names
 */
int validateArguments(int argc, char** argv, char* inFileName,
    char* outFileName)
{
    int validArgCount = 0, inFileFound = 0, outFileFound = 0;

    /* First check if correct number of arguments */
    if (argc == 5)
    {
        validArgCount = 1;
        /* Check for an input file */
        if (*argv[1] == 'i')
        {
            strcpy(inFileName, argv[2]);
            inFileFound = 1;
        }
        else if (*argv[3] == 'i')
        {
            strcpy(inFileName, argv[4]);
            inFileFound = 1;
        }

        /* Check for an output file */
        if (*argv[1] == 'o')
        {
            strcpy(outFileName, argv[2]);
            outFileFound = 1;
        }
        else if (*argv[3] == 'o')
        {
            strcpy(outFileName, argv[4]);
            outFileFound = 1;
        }
    }

    return validArgCount && inFileFound && outFileFound;
}

/**
 * SUBMODULE: usage
 * IMPORT: error
 * EXPORT: None
 * Displays the error message along with the correct way to use the program
 *      to the user
 */
void usage(char* error)
{
    printf("%s\nCorrect Usage: ./main i <infile> o <outfile>", error);
}

void displayOuterList(LinkedList* headerList, LinkedList* outerList)
{
    Node* headerCurrentNode;
    Node* outerCurrentNode;

    LinkedList* innerList;
    Node* innerCurrentNode;
    HeaderInfo* headerInfo;

    int* tmp;
    outerCurrentNode = outerList->head;

    while (outerCurrentNode != NULL)
    {
        innerList = (LinkedList*) outerCurrentNode->value;
        innerCurrentNode = innerList->head;
        headerCurrentNode = headerList->head;

        while (innerCurrentNode != NULL)
        {
            headerInfo = (HeaderInfo*) headerCurrentNode->value;
            if (strcmp(headerInfo->type, "string") == 0)
            {
                printf("%s", (char*) innerCurrentNode->value);
            }
            else if (strcmp(headerInfo->type, "integer") == 0)
            {
                if (innerCurrentNode->value != NULL)
                {
                    printf("%d,", *(int*) innerCurrentNode->value);
                }
                else
                {
                    printf(" ,");
                }
            }
            innerCurrentNode = innerCurrentNode->next;
            headerCurrentNode = headerCurrentNode->next;
        }

        printf("\n");

        outerCurrentNode = outerCurrentNode->next;
    }
}
