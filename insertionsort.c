#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int insert(LinkedList* linkedList, LinkedList* new, HeaderInfo* header,
    int headerIndex)
{
    LinkedList* currentList;
    Node *currentNode, *nextNode;
    Node* compareNode;

    int posFound = 0;

    int i = 0;

    Node* searchNode = findIndex(new, headerIndex);

    currentNode = linkedList->head;

    // Loop through linkedList until end
    while ((i < linkedList->size) && (!posFound))
    {
        currentList = (LinkedList*) currentNode->value;
        compareNode = findIndex(currentList, headerIndex);

        if (strcmp(header->type, "integer") == 0)
        {
            if (compareNode->value == NULL)
            {

            }
            else
            {
                if ((*(int*) compareNode->value) > (*(int*) searchNode->value))
                {

                }
            }
        }
        else
        {
            
        }

        currentNode = currentNode->next;
        i ++;
    }
}
