#include "../include/queue.h"

void queueInitialize(Queue* queue){
    queue->first = NULL;
    queue->last = NULL;
}

//add to last
void queuePush(Queue* queue, void* value){
    queueNode* node = (queueNode*)malloc(sizeof(queueNode));
    node->value = value;
    node->sig = NULL;

    if(queue->last == NULL)
        queue->first = node;
    else
        queue->last->sig = node;

    queue->last = node;
}

//remove from first
void* queuePop(Queue* queue){
    queueNode* node = queue->first;
    void* value = node->value;
    
    if(queue->first == queue->last)
        queue->first = queue->last = NULL;
    else
        queue->first = node->sig;

    free(node);
    return value;
}

int queueIsEmpty(Queue queue){
    return queue.last == NULL;
}

void* queuePeek(Queue queue){
    return queue.first->value;
}