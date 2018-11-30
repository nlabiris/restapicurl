#ifndef H_LIST
#define H_LIST

typedef struct _node {
    void *data;
    struct _node *next;
} Node;

typedef struct _linkedList {
    Node *head;
    Node *tail;
    Node *current;
} LinkedList;

typedef void(*DISPLAY)(void*);
typedef int(*COMPARE)(void*, void*);

void initializeList(LinkedList *list);
void addHead(LinkedList *list, void *data);
void addTail(LinkedList *list, void* data);
Node *getNode(LinkedList *list, COMPARE compare , void* data);
void deleteNode(LinkedList *list, Node *node);
void freeList(LinkedList *list);

#endif