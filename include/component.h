#ifndef COMPONENT_H
#define COMPONENT_H

#include <stdio.h>
#include <stdlib.h>
#include "operation.h"

#define COMPONENT_MAX_PARAM 32

typedef struct{
    char symbol;
    void* parameters[COMPONENT_MAX_PARAM];
    int cantParameters;
}componentT;

typedef componentT* Component;

Component createComponent(char symbol);
void componentAddParameter(Component component, void* parameter);
void componentAddValue(Component component, double value);
void componentGetValues(double* values, Component valuesComponent);
void componentValuesToString(char* componentStr, Component valuesComponent, int numStrTam);
Component cloneValuesComponent(Component component);
void freeValuesComponent(void* component);
Component componentStringToValues(char* componentStr);

#endif