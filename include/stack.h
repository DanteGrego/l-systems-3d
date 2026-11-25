#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef struct stackNode{
    void* value;
    struct stackNode* sig; 
}stackNode;

typedef stackNode* Stack;

void stackInitialize(Stack* stack);
void stackPush(Stack* stack, void* value);
void* stackPop(Stack* stack);
void* stackPeek(Stack stack);
int stackIsEmpty(Stack stack);

#endif