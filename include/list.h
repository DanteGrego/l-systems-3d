#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct listNode{
    void* value;
    struct listNode* sig;
}listNode;

typedef listNode* List;

void listInitialize(List* list);
listNode* createListNode(void* value);
void listAppend(List* list, listNode* elementAppend);
void freeListNode(listNode* node, void (valueDestructor)(void*));
void freeList(List list, void (valueDestructor)(void*));

#endif