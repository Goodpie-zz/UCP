 /**
 * FILE:        testcases.c
 * AUTHOR:      Brandyn Britton
 * USERNAME:    18265716
 * UNIT:        UCP
 * PURPOSE:     Provide test cases for the assignment modules
 * COMMENTS:
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "testcases.h"
#include "linkedlist.h"

int testRemoveLinkedList(LinkedList*);

int main(int argc, char* argv[])
{
    testLinkedList();

    return 0;
}

void testLinkedList()
{
    int i;
    char* testElement;
    int testElements = 20;
    LinkedList* testList;
    Node* testNode;

    /* Create Linked List */
    testList = createLinkedList();

    /* Populate linked list */
    for (i = 0; i < testElements; i ++)
    {
        testElement = (char*) malloc(sizeof(char) * 20);
        strcpy(testElement, "This is a test");
        insertLast(testList, testElement);
    }

    testRemoveLinkedList(testList);

    /* Test find index */
    testNode = findIndex(testList, 5);
    printf("search for 5th node with value: %s\n", (char*) testNode->value);

    /* Test insert first */
    testElement = (char*) malloc(sizeof(char) * 20);
    strcpy(testElement, "First element");
    insertFirst(testList, testElement);

    /* Test free */
    freeLinkedList(testList);

}

int testRemoveLinkedList(LinkedList* testList)
{
    Node* testNode;
    int success = 1;
    LinkedList* newList = createLinkedList();

    testNode = removeFirst(testList);
    if (testNode != NULL)
    {
        free(testNode->value);
        free(testNode);
    }
    else
    {
        success = 0;
    }

    testNode = removeLast(testList);
    if (testNode != NULL)
    {
        free(testNode->value);
        free(testNode);
    }
    else
    {
        success = 0;
    }

    testNode = removeFirst(newList);
    if (testNode != NULL)
    {
        success = 0;
    }

    testNode = removeLast(newList);
    if (testNode != NULL)
    {
        success = 0;
    }

    free(newList);

    return success;

}
