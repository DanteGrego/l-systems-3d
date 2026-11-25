#include "../include/operation.h"

char precedenceList[] = {'_', '<', '>', '^', '*', '/', '+', '-'};

Operation createOperation(){
    Operation operation = (Operation)malloc(sizeof(operationT));
    operation->cantTokens = 0;
    return operation;
}

void operationAddToken(Operation operation, Token token){
    operation->tokens[operation->cantTokens] = token;
    (operation->cantTokens)++;
}

double solveOperation(Operation operation, double *variableValues)
{
    Stack operationStack;
    stackInitialize(&operationStack);

    for(int i = 0; i < operation->cantTokens; i++)
    {
        Token actToken = operation->tokens[i];

        switch(actToken->id){
            case TOKEN_OPERATOR_ID:
                Token operand = stackPop(&operationStack);
                Token result = stackPop(&operationStack);
                double value = *(double *)operand->value;
                double resultValue = *(double *)result->value;
                freeToken(operand);
                freeToken(result);
                switch (*(char *)actToken->value)
                {
                case '+':
                    resultValue += value;
                    break;
                case '-':
                    resultValue -= value;
                    break;
                case '*':
                    resultValue *= value;
                    break;
                case '/':
                    resultValue /= value;
                    break;
                case '>':
                    resultValue = resultValue > value;
                    break;
                case '<':
                    resultValue = resultValue < value;
                    break;
                case '_':
                    resultValue = resultValue == value;
                    break;
                case '^':
                    resultValue = pow(resultValue, value);
                    break;
                }
                actToken = createNumberToken(resultValue);
                break;
            case TOKEN_RELATIVE_VARIABLE_ID:
                actToken = generateNumberToken(actToken, variableValues);
                break;
            case TOKEN_INMEDIATE_ID:
                actToken = createNumberToken(*(double*)actToken->value);
                break;
        }
        stackPush(&operationStack, actToken);
    }

    Token resultToken = stackPop(&operationStack);
    double result = *(double*)resultToken->value;
    freeToken(resultToken);

    return result;
}

Operation readOperationPostfix(char *operationStr, int operationBegin, char *operationVariables)
{
    Operation operation = createOperation();

    int i = operationBegin;

    while (operationStr[i] != ';')
    {
        while (operationStr[i] == ' ') i++;
        if (operationStr[i] != ';')
        {
            if (isalpha(operationStr[i]))
            { // variable
                int varPos = strchr(operationVariables, operationStr[i]) - operationVariables;
                operationAddToken(operation, createRelativeVariableToken(varPos));
            }
            else if (isdigit(operationStr[i]))
            { // number
                double inm = strtod(operationStr + i, NULL);
                operationAddToken(operation, createNumberToken(inm));
                while (operationStr[i] != ' ')
                    i++;
            }
            else
            { // operator
                operationAddToken(operation, createOperatorToken(operationStr[i]));
            }
            i++;
        }
    }

    return operation;
}


Operation readOperationInfix(char* operationStr, char* operationVariables){
    Operation operation = createOperation();
    Stack stack;
    stackInitialize(&stack);
    int i = 0;

    while(operationStr[i] != ';'){
        while(operationStr[i] == ' ') i++;

        if(isdigit(operationStr[i])){//operand inm
            double inm = strtod(operationStr+i, NULL);
            operationAddToken(operation, createNumberToken(inm));
            while(isdigit(operationStr[i]) || operationStr[i] == '.') i++;
        }else if(isalpha(operationStr[i])){//operand var
            int varPos = strchr(operationVariables, operationStr[i]) - operationVariables;
            operationAddToken(operation, createRelativeVariableToken(varPos));
            i++;
        }else if(operationStr[i] == '('){
            stackPush(&stack, createOperatorToken(operationStr[i]));
            i++;
        }else if(operationStr[i] == ')'){
            Token token = stackPop(&stack);
            while(token != NULL && *(char*)token->value != '('){//in the stack all are operands
                operationAddToken(operation, token);
                token = stackPop(&stack);
            }
            freeToken(token);
            i++;
        }else{
            int actPrecedence = strchr(precedenceList, operationStr[i]) - precedenceList;
            Token token = stackPeek(stack);
            while(token != NULL && *(char*)token->value != '(' && strchr(precedenceList, *(char*)token->value) - precedenceList <= actPrecedence){
                token = stackPop(&stack);
                operationAddToken(operation, token);
                token = stackPeek(stack);
            }
            stackPush(&stack, createOperatorToken(operationStr[i]));
            i++;
        }
    }

    while(!stackIsEmpty(stack)){
        Token token = stackPop(&stack);
        operationAddToken(operation, token);
    }

    return operation;
}