/**
* FILE:        linkedlist.h
* AUTHOR:      Brandyn Britton
* USERNAME:    18265716
* UNIT:        UCP
* PURPOSE:     UCP Assignment 2016 Semester 2
* COMMENTS:    Header file for linkedlist.c
*/

/* Struct defining the structure of a node for linked list */
typedef struct Node {
	void* value;
	struct Node* next;
	struct Node* prev;
} Node;

/* Struct defining the structure of a linked list */
typedef struct {
	Node* head;
	Node* tail;
	int size;
} LinkedList;

/**
 * SUBMODULE: createLinkedList
 * IMPORT: None
 * EXPORT: linkedList
 * Creates a new linked list
 */
LinkedList* createLinkedList();

/**
 * SUBMODULE: insertFirst
 * IMPORT: linkedList, value
 * EXPORT: None
 * Inserts an element into the head of the linked list
 */
void insertFirst(LinkedList*, void*);

/**
 * SUBMODULE: insertLast
 * IMPORT: linkedList, value
 * EXPORT: None
 * Inserts an element into the tail of the linked list
 */
void insertLast(LinkedList*, void*);

/**
 * SUBMODULE: removeFirst
 * IMPORT: linkedList
 * EXPORT: headNode
 * Removes the head node from the linked list
 */
Node* removeFirst(LinkedList*);

/**
 * SUBMODULE: removeLast
 * IMPORT: linkedList
 * EXPORT: tailNode
 * Removes the tail node of the linked list
 */
Node* removeLast(LinkedList*);

/*
 * SUBMODULE: findIndex
 * IMPORT: LinkedList*, int
 * EXPORT: None
 * Finds the value stored at index of LinkedList
 */
void* findIndex(LinkedList*, int);

/*
 * SUBMODULE: swapNodes
 * IMPORT: Node*, Node*
 * EXPORT: None
 * Swaps the position of two Nodes
 */
void swapNodes(Node*, Node*);

/*
 * SUBMODULE: swapNodesByIndex
 * IMPORT: LinkedList, int, int
 * EXPORT: None
 * Swaps two nodes at given indexes
 */
void swapNodesByIndex(LinkedList*, int, int);

/**
 * SUBMODULE: linkedListIsEmpty
 * IMPORT: linkedList
 * EXPORT: (int) boolean
 * Function more for readability
 */
int linkedListIsEmpty(LinkedList*);

/**
 * SUBMODULE: freeLinkedList
 * IMPORT: LinkedList* linkedList
 * EXPORT: None
 * Frees all elements within the linkedList
 */
void freeLinkedList(LinkedList*);
