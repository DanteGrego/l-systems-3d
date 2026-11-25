#include "../include/rule.h"

Rule createRule(char* ruleStr){
    Rule rule = (Rule)malloc(sizeof(ruleT));

    char paramSymbols[32];
    int i = 0;

    while(ruleStr[i] == ' ') i++;

    rule->predecessorSymbol = ruleStr[i];
    
    i++;
    int cantParam = 0;
    if(ruleStr[i] == '('){
        i++;
        while(ruleStr[i] != ')'){    
            paramSymbols[cantParam] = ruleStr[i];
            cantParam++;
            i++;
            while(ruleStr[i] != ')' && !isalpha(ruleStr[i])) i++;
        }
    }
    rule->predecessorCantParam = cantParam;
    
    while(ruleStr[i] != ':' && (ruleStr[i] != '-' || ruleStr[i+1] != '>')) i++;

    if(ruleStr[i] == ':'){
        i++;
        rule->condition = readOperationInfix(ruleStr+i, paramSymbols);
    }else
        rule->condition = readOperationInfix("1;", NULL);

    while(ruleStr[i-1] != '-' || ruleStr[i] != '>') i++; 
    i++;

    rule->cantSuccessors = 0;
    while(ruleStr[i] != '\0'){
        while(ruleStr[i] == ' ' && ruleStr[i] != '\0') i++;

        if(ruleStr[i] != '\0'){
            Component successor = createComponent(ruleStr[i]);
            i++;
            if(ruleStr[i] == '('){
                i++;
                while(ruleStr[i] != ')'){
                    while(ruleStr[i] == ' ' || ruleStr[i] == ',') i++;
                    componentAddParameter(successor, readOperationInfix(ruleStr+i, paramSymbols));
                    while(ruleStr[i] != ',' && ruleStr[i] != ')') i++;
                }
                i++;
            }


            rule->successors[rule->cantSuccessors] = successor;
            (rule->cantSuccessors)++;
        }
    }

    return rule;
}

List applyRule(Rule rule, Component component){
    List successors;
    listInitialize(&successors);
    
    double operationValues[COMPONENT_MAX_PARAM];
    componentGetValues(operationValues, component);

    for(int i = 0; i < rule->cantSuccessors; i++){
        Component succesorRule = rule->successors[i];
        Component newComponent = createComponent(succesorRule->symbol);
            
        for(int j = 0; j < succesorRule->cantParameters; j++){
            componentAddValue(newComponent, solveOperation((Operation)succesorRule->parameters[j], operationValues));
        }

        listAppend(&successors, createListNode(newComponent));
    }

    return successors;
}

int canApplyRule(Rule rule, Component component){
    int cond = 0;

    if(rule->predecessorSymbol == component->symbol && rule->predecessorCantParam == component->cantParameters){
        double componentValues[COMPONENT_MAX_PARAM];
        componentGetValues(componentValues, component);
        cond = solveOperation(rule->condition, componentValues);
    }

    return cond;
}