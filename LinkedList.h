typedef struct Node {
	void* value;
	struct Node* next;
} Node;

typedef struct {
	Node* head;
	int size;
	Node* tail;
} LinkedList;

void insertFirst(LinkedList*, void*);
void insertLast(LinkedList*, void*);

void* peekFIrst(LinkedList*);
void peekLast(LinkedList*);

void deleteList(LinkedList*);
