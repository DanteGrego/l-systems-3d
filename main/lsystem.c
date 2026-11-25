#include "../include/lsystem.h"

Lsystem createLsystem(){
    Lsystem lsystem = (Lsystem)malloc(sizeof(lsystemT));
    listInitialize(&lsystem->iterationComponents);
    lsystem->cantRules = 0;
    return lsystem;
}

void lsystemAddRule(Lsystem lsystem, Rule rule){
    lsystem->rules[lsystem->cantRules] = rule;
    (lsystem->cantRules)++;
}

void lsystemSetComponents(Lsystem lsystem, List components){
    lsystem->iterationComponents = components;
}

void lsystemIterate(Lsystem lsystem){
    List nextIteration;
    listInitialize(&nextIteration);

    for(listNode* node = lsystem->iterationComponents; node != NULL; node = node->sig){
        int j = 0;
        while(j < lsystem->cantRules && !canApplyRule(lsystem->rules[j], node->value))
            j++;
        
        if(j < lsystem->cantRules){
            List successors = applyRule(lsystem->rules[j], node->value);
            listAppend(&nextIteration, successors);
        }else
            listAppend(&nextIteration, createListNode(cloneValuesComponent(node->value)));
    } 

    freeList(lsystem->iterationComponents, freeValuesComponent);
    lsystemSetComponents(lsystem, nextIteration);
}

void lsystemIterationToString(char* iterationStr, Lsystem lsystem, int numStrTam){
    int i = 0;
    for(listNode* node = lsystem->iterationComponents; node != NULL; node = node->sig){
        componentValuesToString(iterationStr+i, node->value, numStrTam);
        while(iterationStr[i] != '\0') i++;
    }
}

List lsystemStringToComponentList(char* iterationStr){
    int i = 0;
    List compList;
    listInitialize(&compList);
    
    while(iterationStr[i] != '\0'){
        Component comp = componentStringToValues(iterationStr+i);
        listAppend(&compList, createListNode(comp));
        while(iterationStr[i] != comp->symbol) i++;
        if(comp->cantParameters > 0) 
            while(iterationStr[i] != ')') i++;
        i++;
    }

    return compList;
}