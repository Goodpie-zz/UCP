#Unix and C Programming Assignment 2016 Semester 2

## Files Submitted

* boolean.h - Allows the use of TRUE and FALSE instead of 1 and 0
* csvparser.c - Parses CSV file with the format specified by the assignment
                documentation
* csvparser.h - Header file for csvparser.c
* filereader.c - Provides functionality for reading files
* filereader.h - Header file for filereader.c
* headerinfo.c - Provides definitions and functionality realting to row headers
* headerinfo.h - Header file for headerinfo.c
* insertionsort.c - Sorts the read in data from the CSV file using user params
* insertionsort.h - Header file for insertionsort.c
* linkedlist.c - Provides functionality for the linked list data structure
* linkedlist.h - Header file for linkedlist.c and provides definitions for
                 linked lists
main.c - Controls the flow of the program
Makefile - Makefile to compile the program
README.txt - see README.txt

## How much of the assignment has been attempted?

All of it. To the best of my knowledge, the whole assignment has been
successfully completed without any errors or loss of functionality

## Known Bugs

None™

## Tested On

Tested on 8DWZF2S in 314.221

## Usage

Compile: $ make

Clean Objects: $ make clean

Clean Objects and Exectuables: $ make very-clean

Usage: main i <inFile> o <outFile>

## Assumptions Made

* Within the assignment outline, missing values are seperated by a space.
This format has been assumed when reading the file and outputting.
* Column headers (name + type) will not exceed more than 4096 characters
* No spaces in column headers
* Files are stored in the same directory as the executable and file names
do not exceed more than 260 characters to play safe with Windows systems
