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
} List;

typedef void(*DISPLAY)(void*);
typedef int(*COMPARE)(void*, void*);

void initializeList(List **list);
void addHead(List **list, void *data);
void addTail(List **list, void* data);
Node *getNode(List **list, COMPARE compare , void* data);
void deleteNode(List **list, Node *node);
void freeList(List **list);

#endif