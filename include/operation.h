#ifndef OPERATIONSOLVER_H
#define OPERATIONSOLVER_H

#define OPERATION_MAX_TOKENS 64

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "token.h"
#include "stack.h"
#include "queue.h"

extern char precedenceList[];

typedef struct{
    Token tokens[OPERATION_MAX_TOKENS];
    int cantTokens;
}operationT;

typedef operationT* Operation;

Operation createOperation();
void operationAddToken(Operation operation, Token token);
double solveOperation(Operation operation, double* variableValues);
Operation readOperationPostfix(char* operationStr, int operationBegin, char* operationVariables);
Operation readOperationInfix(char* operationStr, char* operationVariables);


#endif