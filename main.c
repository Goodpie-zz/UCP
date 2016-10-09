#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "csvparser.h"
#include "filereader.h"

#ifndef LINKEDLIST_H
	#define LINKEDLIST_H
	#include "linkedlist.h"
#endif

/* Max filename size is 255. Assuming file is in same directory */
#define MAX_FILENAME_SIZE 255

int main(int argc, char* argv[])
{
	int validFileParams;
	int validInFile;
	int validOutFile;

	char inFileName[MAX_FILENAME_SIZE];
	char outFileName[MAX_FILENAME_SIZE];

	/* Create linked list and default value of NULL for error handling */
	LinkedList* dataList = NULL;
	LinkedList* headerList = NULL;

	FILE* inFile;
	FILE* outFile;

	int parsedCSV;

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
		else
		{
			validInFile = openFile(&inFile, inFileName, "r");
			validOutFile = openFile(&outFile, outFileName, "w");

			if (validInFile && validOutFile)
			{
				parsedCSV = parseCSV(inFile, &dataList, &headerList);
				if (parsedCSV)
				{
					freeLinkedList(dataList);
					freeHeaderLinkedList(headerList);
				}
				else
				{
					printf("Exiting: Invalid CSV file format");
					freeLinkedList(dataList);
					freeLinkedList(headerList);
				}

				fclose(inFile);
				fclose(outFile);
			}
			else
			{
				if (!validInFile)
				{
					fclose(outFile);
				}
				else
				{
					fclose(inFile);
				}
			}
		}
	}

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
	printf("Correct Usage:\n$ sortingAssignment i <inFile> o <outfile>\n");
}
