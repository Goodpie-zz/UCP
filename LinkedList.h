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

LinkedList* createLinkedList(void*);

void insertFirst(LinkedList*, void*);
void insertLast(LinkedList*, void*);

void* peekFirst(LinkedList*);
void peekLast(LinkedList*);

void* removeLast(LinkedList*);
void* removeFirst(LinkedList*);

void deleteList(LinkedList*);
