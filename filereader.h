/**
* FILE:         filereader.h
* AUTHOR:       Brandyn Britton
* USERNAME:     18265716
* UNIT:         UCP
* PURPOSE:      UCP Assignment 2016 Semester 2
* COMMENTS:     Headerfile for filereader.c
*/

/**
 * SUBMODULE: openFile
 * IMPORT: FILE**, char*, char*
 * EXPORT: int
 * Opens a file
 */
int openFile(FILE**, char*, char*);

/**
 * SUBMODULE: readLine
 * IMPORT: FILE*, int*
 * EXPORT: char*
 * Reads in line of unknown size 
 */
char* readLine(FILE*, int*);
