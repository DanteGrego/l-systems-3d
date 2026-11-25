#include "../include/token.h"

Token getNewToken(){
    return (Token)malloc(sizeof(token));
}

Token createNumberToken(double value){
    Token token = getNewToken();
    token->id = TOKEN_INMEDIATE_ID;
    double* val = (double*)malloc(sizeof(double));
    *val = value;
    token->value = val;
    return token;
}

Token createOperatorToken(char op){
    Token token = getNewToken();
    token->id = TOKEN_OPERATOR_ID;
    char* tokenOp = (char*)malloc(sizeof(char));
    *tokenOp = op;
    token->value = tokenOp;
    return token;
}

Token createVariableToken(void* variable){
    Token token = getNewToken();
    token->id = TOKEN_VARIABLE_ID;
    token->value = variable;
    return token;
}

Token createRelativeVariableToken(int variablePos){
    Token token = getNewToken();
    token->id = TOKEN_RELATIVE_VARIABLE_ID;
    int* val = (int*)malloc(sizeof(int));
    *val = variablePos;
    token->value = val;
    return token;
}

Token generateNumberToken(Token relativeVariableToken, double* variableOrigin){
    int varPos = *(int*)relativeVariableToken->value;
    double value = *(variableOrigin + varPos);
    return createNumberToken(value);
}

void freeToken(Token token){
    if(token != NULL){
        free(token->value);
        free(token);
    }
}