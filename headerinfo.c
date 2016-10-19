#include <stdlib.h>

#include "headerinfo.h"

/**
 * SUBMODULE: freeHeaderLinkedList
 * IMPORT: LinkedList*
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
 * IMPORT: HeaderInfo* EXPORT: None
 * Handles freeing a HeaderInfo struct pointer
 */
void freeHeader(HeaderInfo* header)
{
    free(header->name);
    free(header->type);
    free(header);
}
