#ifndef RULE_H
#define RULE_H

#include <string.h>
#include <stdio.h>
#include "component.h"
#include "operation.h"
#include "list.h"

#define RULE_MAX_SUCCESSORS 32

typedef struct{
    char predecessorSymbol;
    int predecessorCantParam;
    Operation condition;
    Component successors[RULE_MAX_SUCCESSORS];
    int cantSuccessors;
}ruleT;

typedef ruleT* Rule;

Rule createRule(char* ruleStr);
List applyRule(Rule rule, Component component);
int canApplyRule(Rule rule, Component component);

#endif