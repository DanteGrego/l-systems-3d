#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

typedef struct queueNode{
    void* value;
    struct queueNode* sig;
}queueNode;

typedef struct{
    queueNode *first, *last;
}Queue;

void queueInitialize(Queue* queue);
void queuePush(Queue* queue, void* value);//add to last
void* queuePop(Queue* queue);//remove from first
int queueIsEmpty(Queue queue);
void* queuePeek(Queue queue);

#endif