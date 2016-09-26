#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "LinkedList.h"

/* Max filename size is 255. Assuming file is in same directory */
#define MAX_FILENAME_SIZE 255

int main(int argc, char* argv[])
{
	char* inFileName;
	char* outFileName;
	int validFileParams;
	LinkedList* linkedList;
	int* testValue;

	testValue = (int*) malloc(sizeof(int));
	*testValue = 10;

	/* Allocate memory to the file names */
	inFileName = (char*) malloc(sizeof(char) * MAX_FILENAME_SIZE);
	outFileName = (char*) malloc(sizeof(char) * MAX_FILENAME_SIZE);

	if (argc != 5)
	{
		/* Invalid number of arguments to function correctly */
		printf("Invalid number of arguments\n");
		displayCorrectUsage();
	}
	else
	{
		/* Chech if correct arguments provided */
		validFileParams = getIOFiles(argv, inFileName, outFileName);
		if (validFileParams == 0)
		{
			displayCorrectUsage();
		}
	}


	linkedList = createLinkedList();
	insertFirst(linkedList, testValue);
	printf("Value found at 0: %d\n", *((int*) findIndex(linkedList, 0)));
	*testValue = 100;
	insertLast(linkedList, testValue);
	removeLast(linkedList);
	deleteList(linkedList);

	/* Free all allocated variables */
	free(inFileName);
	free(outFileName);
	
	return 0;		
}

/**
 * SUBMODULE getIOFiles
 * IMPORT char**, char*, char* EXPORT int (boolean)
 * Checks the arguments for the correct parameters for filenames
 */
int getIOFiles(char** args, char* inFileName, char* outFileName)
{
	int inFileFound = 0;
	int outFileFound = 0;
	
	/* Check for an input file parameter */
	if (*args[1] == 'i')
	{
		strcpy(inFileName, args[2]);
		inFileFound = 1;
	}
	else if (*args[3] == 'i')
	{
		strcpy(inFileName, args[4]);
		inFileFound = 1;
	}

	/* Check for an output file */
	if (*args[1] == 'o')
	{
		strcpy(outFileName, args[2]);
		outFileFound = 1;
	}
	else if (*args[3] == 'o')
	{
		strcpy(outFileName, args[4]);
		outFileFound = 1;
	}
	
	return inFileFound && outFileFound;
}

/**
 * SUBMODULE displayCorrectUsage
 * IMPORT None EXPORT None
 * Displays the correct way to use the program
 */
void displayCorrectUsage()
{
	printf("Correct Usage:\n\t$ sortingAssignment i inFile o outfile\n");
}
