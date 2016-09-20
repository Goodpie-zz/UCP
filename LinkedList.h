typedef struct Node {
	void* value;
	struct Node* next;
} Node;

typedef struct {
	Node* head;
	int size;
	Node* tail;
} LinkedList;

LinkedList* createLinkedList(void*);

void insertFirst(LinkedList*, void*);
void insertLast(LinkedList*, void*);

void* peekFirst(LinkedList*);
void peekLast(LinkedList*);

void* removeLast(LinkedList*);

void deleteList(LinkedList*);
