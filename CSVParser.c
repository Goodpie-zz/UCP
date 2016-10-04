/*
 * =====================================================================================
 *
 *       Filename:  CSVParser.c
 *
 *    Description:  Parses CSV File
 *
 *        Version:  1.0
 *        Created:  30/09/2016 12:43:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "CSVParser.h"

#define LINE_LENGTH 4096

LinkedList* parseCSV(FILE* inFile)
{	
	LinkedList* linkedList;
	int currentLine = 0;
	int currentSize = LINE_LENGTH; /* initial buffer size */
	char* buffer = (char*) malloc(sizeof(char) * currentSize);
	char ch = fgetc(inFile);

	while ( ch != EOF )
	{
		if (ch == '\n')
		{
			currentLine += 1;
		}
		
		printf("%c", ch);
		ch = fgetc(inFile);
	}

	linkedList = createLinkedList();

	free(buffer);

	return linkedList;
}

void defineHeaders(char* line, char** headers)
{
	
}










