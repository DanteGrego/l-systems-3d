#include "../include/stack.h"

void stackInitialize(Stack* stack){
    *stack = NULL;
}

void stackPush(Stack* stack, void* value){
    stackNode* node = (stackNode*)malloc(sizeof(stackNode));
    node->value = value;
    node->sig = *stack;
    *stack = node;
}

void* stackPop(Stack* stack){
    void* val;
    if(*stack == NULL)
        val = NULL;
    else{
        stackNode* node = *stack;
        *stack = node->sig;
        val = node->value;
        free(node);
    }
    return val;
}

void* stackPeek(Stack stack){
    if(stack == NULL)
        return NULL;
    else
        return stack->value;
}

int stackIsEmpty(Stack stack){
    return stack == NULL;
}