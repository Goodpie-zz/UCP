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

#include "csvparser.h"
#include "filereader.h"
#include "headerinfo.h"
#include "boolean.h"
#include "insertionsort.h"

/* Assuming file name can only have a max of 255 chars */
#define MAX_FILENAME_SIZE 255

void writeListToFile(LinkedList*, LinkedList*, FILE*);
static int openIOFiles(FILE**, FILE**, char*, char*);
static int validateArguments(int, char**, char*, char*);
static void usage(char*);
static int displayMenu(LinkedList*);
static int displayOrderMenu();
static int getMenuInput(int max);

/**
 * SUBMODULE: main
 * IMPORT: argc, argv[]
 * EXPORT: int
 * Controls the main flow of the program
 */
 /* TODO: shorten this function */
int main(int argc, char* argv[])
{
    FILE *inFile = NULL, *outFile = NULL;
    int validFiles;
    int sortOption, sortOrder;
    char inFileName[MAX_FILENAME_SIZE], outFileName[MAX_FILENAME_SIZE];
    HeaderInfo* sortHeader;

    LinkedList* dataList = NULL;
    LinkedList* headerList = NULL;

    if (validateArguments(argc, argv, inFileName, outFileName))
    {
        validFiles = openIOFiles(&inFile, &outFile, inFileName, outFileName);
        if (validFiles)
        {
            if (parseCSV(inFile, &dataList, &headerList))
            {
                sortOption = displayMenu(headerList);
                sortOrder = displayOrderMenu();
                sortHeader = (HeaderInfo*) findIndex(headerList, sortOption);
                sortList(dataList, sortHeader, sortOrder);
                writeListToFile(headerList, dataList, outFile);
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
    }
    else
    {
        /* Show user how to use program */
        usage("Invalid arguments provided");
    }

    return 0;
}

int openIOFiles(FILE** inFile, FILE** outFile, char* inFileName, char* outFileName)
{
    /* Flags for invalid files */
    int validInFile, validOutFile;

    /* Check IO files for errors */
    validInFile = openFile(inFile, inFileName, "r");
    validOutFile = openFile(outFile, outFileName, "w");

    /* on file invalid so close based on which one failed */
    if (!validInFile)
    {
        fclose(*outFile);
    }
    else if (!validOutFile)
    {
        fclose(*inFile);
    }

    return validInFile && validOutFile;
}

/**
 * SUBMODULE: validateAguments
 * IMPORT: argc, argv, inFileName, outFileName
 * EXPORT: (int) boolean
 * Checks whether the arguments provided by the user are valid and also
 *      determines the correct file names
 */
int validateArguments(int argc, char** argv, char* inFileName, char* outFileName)
{
    int validArgCount = FALSE, inFileFound = FALSE, outFileFound = FALSE;

    /* First check if correct number of arguments */
    if (argc == 5)
    {
        validArgCount = TRUE;
        /* Check for an input file */
        if (*argv[1] == 'i')
        {
            strcpy(inFileName, argv[2]);
            inFileFound = TRUE;
        }
        else if (*argv[3] == 'i')
        {
            strcpy(inFileName, argv[4]);
            inFileFound = TRUE;
        }

        /* Check for an output file */
        if (*argv[1] == 'o')
        {
            strcpy(outFileName, argv[2]);
            outFileFound = TRUE;
        }
        else if (*argv[3] == 'o')
        {
            strcpy(outFileName, argv[4]);
            outFileFound = TRUE;
        }
    }

    return validArgCount && inFileFound && outFileFound;
}

/**
 * SUBMODULE: displayMenu
 * IMPORT: LinkedList* headerList
 * EXPORT: int choice
 * Displays menu and gets user input on their sorting method preference
 */
int displayMenu(LinkedList* headerList)
{
    Node* currentNode;
    HeaderInfo* headerInfo;
    int i;
    int choice = -1; /* Default choice is invalid */

    while ((choice <= 0) || (choice > headerList->size))
    {
        i = 1;
        /* display nice interface to user */
        printf("\n________________________________________ \n");
        printf("\nWhat would you like to sort the data by: \n");
        printf("________________________________________ \n\n");

        /* List through headers and display names of each as menu options */
        currentNode = headerList->head;
        while (currentNode != NULL)
        {
            headerInfo = (HeaderInfo*) currentNode->value;
            printf("%d) %s\n", i, headerInfo->name);
            i ++;
            currentNode = currentNode->next;
        }

        choice = getMenuInput(i);
    }

    /* Return actual index */
    return choice - 1;
}

int displayOrderMenu()
{
    int choice = -1;
    while ((choice < 1) || (choice > 2))
    {
        printf("\n__________________________________________ \n");
        printf("\nWhat order would you like to sort the data: \n");
        printf("__________________________________________ \n\n");
        printf("1) Ascending\n");
        printf("2) Descending\n");
        choice = getMenuInput(2);
    }

    return choice - 1;
}

int getMenuInput(int max)
{
    int choice = -1;
    char c;

    /* Check valid input */
    printf("\nEnter an option between 1-%d: ", max);
    if (scanf("%d", &choice) == 1)
    {
        if ((choice <= 0) || (choice > max))
        {
            printf("Invalid choice: %d\n", choice);
        }
    }
    else
    {
        printf("Invalid choice. Please enter an integer\n");
        choice = -1;

        /* Clear buffer due to incorrect input */
        while ((c = getchar() != '\n') && (c != EOF));
    }

    return choice;
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

void writeListToFile(LinkedList* headerList, LinkedList* dataList, FILE* file)
{
    Node* headerNode;
    HeaderInfo* header;

    Node *dataNode, *innerDataNode;
    LinkedList *innerList;

    /* First loop through the header to create header line */
    headerNode = headerList->head;
    while (headerNode != NULL)
    {
        header = (HeaderInfo*) headerNode->value;
        fprintf(file, "%s (%s)", header->name, header->type);
        if (headerNode->next != NULL)
        {
            fprintf(file, "%s ", ",");
        }
        headerNode = headerNode->next;
    }

    fprintf(file, "\n");

    dataNode = dataList->head;
    while (dataNode != NULL)
    {
        headerNode = headerList->head;
        innerList = (LinkedList*) dataNode->value;
        innerDataNode = innerList->head;

        while (innerDataNode != NULL)
        {
            header = (HeaderInfo*) headerNode->value;
            if (strcmp(header->type, "string") == 0)
            {
                fprintf(file, "%s", (char*) innerDataNode->value);
            }
            else if (strcmp(header->type, "integer") == 0)
            {
                if (innerDataNode->value != NULL)
                {
                    fprintf(file, " %d", *(int*) innerDataNode->value);
                }
                else
                {
                    fprintf(file, " ");
                }
            }
            

            if (innerDataNode->next != NULL)
            {
                fprintf(file, ",");
            }
            else
            {
                fprintf(file, "\n");
            }
            
            /* Get next nodes */
            innerDataNode = innerDataNode->next;
            headerNode = headerNode->next;
        }

        dataNode = dataNode->next;
    }
}
