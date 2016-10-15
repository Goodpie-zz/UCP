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

int main(int argc, char* argv[])
{
    printf("[*] Testing Linked List Operations...\n");
    if(testLinkedList())
    {
        printf("Passed!\n");
    }
    else
    {
        printf("Failed!\n");
    }

    return 0;
}

/**
 * SUBMODULE: testLinkedList
 * IMPORT: None
 * EXPORT: int
 * Tests linked list functionality
 */
int testLinkedList()
{
    LinkedList* linkedList;

    int removeFirstPass, removeLastPass;

    /* Create Linked List */
    linkedList = createLinkedList();

    /* Populate linked list */
    printf("\tPopulating linked list...\n");
    testPopulate(linkedList, 20);

    /* Test removal of elements from linked list */
    printf("\tTesting remove first...\n");
    removeFirstPass = testRemoveFirst(linkedList);
    printf("\tTesting remove last...\n");
    removeLastPass = testRemoveLast(linkedList);

    printf("\tTesting free linked list...\n");
    freeLinkedList(linkedList);

    return removeFirstPass && removeLastPass;

}

/**
 * SUBMODULE: testPopulate
 * IMPORT: LinkedList* linkedList, int count
 * EXPORT: None
 * Populates linked list with strings for testing purposes
 */
void testPopulate(LinkedList* linkedList, int count)
{
    char* value;
    int i;

    for (i = 0; i < count; i ++)
    {
        value = (char*) malloc(sizeof(char) * 20);
        strcpy(value, "This is a test");
        insertLast(linkedList, value);
    }
}


/**
 * SUBMODULE: testRemoveLast
 * IMPORT: LinkedList*
 * EXPORT: int success
 * Tests the remove first functionality of populated and empty linked list
 */
int testRemoveFirst(LinkedList* testList)
{
    int success = 1;
    LinkedList* emptyList = createLinkedList();
    Node* testNode = removeFirst(testList);

    /* First test populated list with result not null */
    if (testNode != NULL)
    {
        free(testNode->value);
        free(testNode);
    }
    else
    {
        success = 0;
    }

    /* Test empty list with result null */
    testNode = removeFirst(emptyList);
    if (testNode != NULL)
    {
        success = 0;
    }

    /* Free the empty list */
    freeLinkedList(emptyList);

    return success;
}


/**
 * SUBMODULE: testRemoveLast
 * IMPORT: LinkedList* linkedList
 * EXPORT: int success
 * Tests the remove last functionality of populated and empty linked list
 */
int testRemoveLast(LinkedList* linkedList)
{
    int success = 1;
    LinkedList* emptyList = createLinkedList();
    Node* testNode = removeLast(linkedList);

    /* Test populated list with result not null */
    if (testNode != NULL)
    {
        free(testNode->value);
        free(testNode);
    }

    /* Test empty list with result null */
    testNode = removeLast(emptyList);
    if (testNode != NULL)
    {
        success = 0;
    }

    freeLinkedList(emptyList);

    return success;
}
