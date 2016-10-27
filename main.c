/**
* FILE:          main.c
* AUTHOR:        Brandyn Britton
* USERNAME:      18265716
* UNIT:          UCP
* PURPOSE:       UCP Assignment 2016 Semester 2
* COMMENTS:      Controls the main flow of the proram  
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

static void writeHeaderToFile(LinkedList*, FILE*);
static void writeListToFile(LinkedList*, LinkedList*, FILE*);
static int openIOFiles(FILE**, FILE**, char*, char*);
static int validateArguments(int, char**, char*, char*);
static void usage(char*);
static int displayMenu(LinkedList*);
static int displayOrderMenu();
static int getMenuInput(int max);
static int sort(LinkedList*, LinkedList*);

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
    int success;
    char inFileName[MAX_FILENAME_SIZE], outFileName[MAX_FILENAME_SIZE];

    LinkedList* dataList = NULL;
    LinkedList* headerList = NULL;

    if (validateArguments(argc, argv, inFileName, outFileName))
    {
        validFiles = openIOFiles(&inFile, &outFile, inFileName, outFileName);
        if (validFiles)
        {
            if (parseCSV(inFile, &dataList, &headerList))
            {

                success = sort(dataList, headerList);
                if (success)
                {
                    printf("Succesfully sorted and stored in %s\n", outFileName);
                }
                else
                {
                    printf("Failed to sort data\n");
                }

                /* Save file to output file */
                writeListToFile(headerList, dataList, outFile);

                /* Free the data */
                freeOuterLinkedList(dataList);
                freeHeaderLinkedList(headerList);
            }
            else
            {
                printf("Exiting: invalid CSV file\n");
            }

            /* Operations finished, close files */
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

/**
 * SUBMODULE: sort
 * IMPORT: dataList, headerList
 * EXPORT: int
 * Handle the initialization of the sort
 */
int sort(LinkedList* dataList, LinkedList* headerList)
{
    int success = TRUE;
    int sortOption, sortOrder;
    HeaderInfo* sortHeader;

    sortOption = displayMenu(headerList);
    sortOrder = displayOrderMenu();

    sortHeader = (HeaderInfo*) findIndex(headerList, sortOption);

    if (sortHeader != NULL)
    {
        /* Check type of data that need sorting */
        if (strcmp(sortHeader->type, "string") == 0)
        {
            /* Data type is a string so use compareString function */
            sortList(dataList, sortOption, sortOrder, compareString);
        }
        else if (strcmp(sortHeader->type, "integer") == 0)
        {
            /* Data type is an integer so use compareInt function */
            sortList(dataList, sortOption, sortOrder, compareInt);
        }
    }
    else
    {
        success = FALSE;
    }

    return success;
}

/**
 * SUBMODULE: openIOFiles
 * IMPORT: inFile, outFile, inFileName, outFileName
 * EXPORT: validFiles
 * Opens both inpu and output files 
 */
int openIOFiles(FILE** inFile, FILE** outFile, char* inFileName, char* outFileName)
{
    /* Flags for invalid files */
    int validFiles, validInFile, validOutFile;

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

    validFiles = validInFile && validOutFile;

    return validFiles;
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

/**
 * SUBMODULE: displayOrderMenu
 * IMPORT: None
 * EXPORT: choice
 * Displays the menu to the user for choosing the order type 
 */
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

/**
 * SUBMODULE: getMenuInput
 * IMPORT: max
 * EXPORT: choice
 * Gets the user choice between 1 and max for menu options
 */
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
    printf("%s\nCorrect Usage: ./main i <infile> o <outfile>\n", error);
}

/**
 * SUBMODULE: writeHeaderToFile
 * IMPORT: headerList, file
 * EXPORT: None
 * Writes the file header information to the output file 
 */
void writeHeaderToFile(LinkedList* headerList, FILE* file)
{
    
    Node* headerNode;
    HeaderInfo* header;
    
    /* First loop through the header to create header line */
    headerNode = headerList->head;
    while (headerNode != NULL)
    {
        header = (HeaderInfo*) headerNode->value;
        fprintf(file, "%s (%s)", header->name, header->type);
        
        /* Check if header node is last in heades. If so, add comma for next header */
        if (headerNode->next != NULL)
        {
            fprintf(file, ", ");
        }
        
        headerNode = headerNode->next;
    }
    
    /* Add new line */
    fprintf(file, "\n");
}

/**
 * SUBMODULE: writeListToFile
 * IMPORT: headerList, dataList, file
 * EXPORT: None
 * Writes the ordered list to the output file 
 */
void writeListToFile(LinkedList* headerList, LinkedList* dataList, FILE* file)
{
    Node* headerNode;
    HeaderInfo* header;

    Node *dataNode, *innerDataNode;
    LinkedList *innerList;
    
    writeHeaderToFile(headerList, file);

    dataNode = dataList->head;
    while (dataNode != NULL)
    {
        headerNode = headerList->head;
        innerList = (LinkedList*) dataNode->value;
        innerDataNode = innerList->head;
        
        /* Loop through the inner linked list */
        while (innerDataNode != NULL)
        {
            header = (HeaderInfo*) headerNode->value;
            
            /* Check type of data */
            if (strcmp(header->type, "string") == 0)
            {
                /* Data is string so we can just save it to file */
                fprintf(file, "%s", (char*) innerDataNode->value);
            }
            else if (strcmp(header->type, "integer") == 0)
            {
                /* Check if integer value is NULL or not */
                if (innerDataNode->value != NULL)
                {
                    fprintf(file, " %d", *(int*) innerDataNode->value);
                }
                else
                {
                    /* NULL value defined by space in CSV file */
                    fprintf(file, " ");
                }
            }
            
            /* Check if last node and add appropriate line endings */
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
