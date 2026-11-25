#include "../include/list.h"

void listInitialize(List* list){
    *list = NULL;
}

listNode* createListNode(void* value){
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->value = value;
    node->sig = NULL;
    return node;
}

void listAppend(List* list, listNode* elementAppend){
    while(*list != NULL)
        list = &(*list)->sig;
    *list = elementAppend;
}

void freeListNode(listNode* node, void (valueDestructor)(void*)){
    valueDestructor(node->value);
    free(node);
}

void freeList(List list, void (valueDestructor)(void*)){
    while(list != NULL){
        listNode* nodeAux = list;
        list = nodeAux->sig;
        freeListNode(nodeAux, valueDestructor);
    }
}