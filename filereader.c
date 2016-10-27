/**
* FILE:         filereader.c
* AUTHOR:       Brandyn Britton
* USERNAME:     18265716
* UNIT:         UCP
* PURPOSE:      UCP Assignment 2016 Semester 2
* COMMENTS:     Handles basic file reading operations
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "boolean.h"

#define LINE_LENGTH 4096

/**
 *  SUBMODULE: openFile
 *  IMPORT: file, filename, mode
 *  EXPORT: success
 *  Attempts to open file and returns true on success
 */
int openFile(FILE** file, char* filename, char* mode)
{
    int success = TRUE;

    *file = fopen(filename, mode);

    /* file can't be opened */
    if (*file == NULL)
    {
        perror("Failed to open file");
        success = FALSE;
    }
    else
    {
        /* file error */
        if (ferror(*file))
        {
            perror("Failed to read/write file");
            fclose(*file);
            success = FALSE;
        }
    }

    return success;
}

/**
 *  SUBMODULE: readLine
 *  IMPORTS: file, endOfFile
 *  EXPORTS: char*
 *  Reads line of unknown size from file and returns true if EOF
 */
char* readLine(FILE* file, int* endOfFile)
{
    int currentIndex = 0;

    int maxSize = LINE_LENGTH;
    char* buffer = (char*) malloc(sizeof(char) * maxSize);
    int ch; /* Int so we can check for EOF */

    do
    {
        ch = fgetc(file);

        /* If not EOF, add to string buffer */
        if (ch != EOF)
        {
            buffer[currentIndex] = (char) ch;
            currentIndex += 1;
        }

        /* Ensure we don't overflow buffer */
        if (currentIndex == (maxSize - 1))
        {
            maxSize *= 2;
            buffer = (char*) realloc(buffer, maxSize);
        }
    } while ((ch != EOF) && ((char) ch != '\n'));

    /* Check EOF */
    if (ch == EOF)
    {
        *endOfFile = TRUE;
    }

    /* Add string terminator */
    buffer[currentIndex] = '\0';
    buffer[strcspn(buffer, "\n")] = 0;

    return buffer;

}
