#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>

#define TOKEN_INMEDIATE_ID 0
#define TOKEN_OPERATOR_ID 1
#define TOKEN_VARIABLE_ID 2
#define TOKEN_RELATIVE_VARIABLE_ID 3

typedef struct{
    char id;
    void* value;
}token;

typedef token* Token;

Token createNumberToken(double value);
Token createOperatorToken(char op);
Token createVariableToken(void* variable);
Token createRelativeVariableToken(int variablePos);
Token generateNumberToken(Token relativeVariableToken, double* variableOrigin);
void freeToken(Token token);

#endif