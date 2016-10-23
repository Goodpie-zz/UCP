typedef struct Node {
	void* value;
	struct Node* next;
	struct Node* prev;
} Node;

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

/**
 * SUBMODULE: findIndex
 * IMPORT: linkedList, index
 * EXPORT: node
 * Gets Node at index from linkedList
 */
Node* findIndex(LinkedList*, int);

/* TODO: Add comments */
void swapNodes(Node**, Node**);

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
