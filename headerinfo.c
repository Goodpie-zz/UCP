/**
* FILE:         headerinfo.c
* AUTHOR:       Brandyn Britton
* USERNAME:     18265716
* UNIT:         UCP
* PURPOSE:      UCP Assignment 2016 Semester 2
* COMMENTS:     Handles operations on HeaderInfo data
*/
#include <stdlib.h>

#include "headerinfo.h"

/**
 * SUBMODULE: freeHeaderLinkedList
 * IMPORT: linkedList
 * EXPORT: None
 * Handles specific case of freeing header list containing HeaderInfo struct
 */
void freeHeaderLinkedList(LinkedList* linkedList)
{
    HeaderInfo* value;
    Node *node, *nextNode;
    node = linkedList->head;

    if (linkedListIsEmpty(linkedList))
    {
        freeLinkedList(linkedList);
    }
    else
    {
        /* Traverse list until last value (where next is NULL) */
        while (node != NULL)
        {
            /* Temporarily assign next node */
            nextNode = node->next;

            /* Cast value to HeaderInfo and free struct */
            value = (HeaderInfo*) node->value;
            freeHeader(value);
            free(node);

            node = nextNode;
        }

        /* Free LinkedList */
        free(linkedList);
    }

}

/**
 * SUBMODULE: freeHeader
 * IMPORT: header 
 * EXPORT: None
 * Handles freeing a HeaderInfo struct pointer
 */
void freeHeader(HeaderInfo* header)
{
    free(header->name);
    free(header->type);
    free(header);
}
