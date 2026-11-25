#include "../include/component.h"

Component createComponent(char symbol){
    Component component = (Component)malloc(sizeof(componentT));

    component->symbol = symbol;
    component->cantParameters = 0;

    return component;
}

void componentAddParameter(Component component, void* parameter){
    component->parameters[component->cantParameters] = parameter;
    (component->cantParameters)++;
}

void componentAddValue(Component component, double value){
    double* valueSpace = (double*)malloc(sizeof(double));
    *valueSpace = value;
    component->parameters[component->cantParameters] = valueSpace;
    (component->cantParameters)++;
}

void componentGetValues(double* values, Component valuesComponent){
    for(int i = 0; i < valuesComponent->cantParameters; i++)
        values[i] = *(double*)valuesComponent->parameters[i];
}

void componentValuesToString(char* componentStr, Component valuesComponent, int numStrTam){
    componentStr[0] = valuesComponent->symbol;
    int j = 1;
    if(valuesComponent->cantParameters > 0){
        componentStr[j++] = '(';

        double values[COMPONENT_MAX_PARAM];
        componentGetValues(values, valuesComponent);
        
        for(int i = 0; i < valuesComponent->cantParameters; i++){
            char valueStr[32];
            snprintf(valueStr, numStrTam, "%f", values[i]);
            int k = 0;
            while(valueStr[k] != '\0')
                componentStr[j++] = valueStr[k++];
            componentStr[j++] = ','; 
            componentStr[j++] = ' ';        
        }
        j -= 2;
            
        componentStr[j++] = ')';
    }
    componentStr[j] = '\0';
}

Component componentStringToValues(char* componentStr){
    int i = 0;
    while(componentStr[i] == ' ') i++;

    Component comp = createComponent(componentStr[i]);
    i++;
    if(componentStr[i] == '(')
        while(componentStr[i] != ')'){
            while(!isdigit(componentStr[i])) i++;
            componentAddValue(comp, strtod(componentStr+i, NULL));
            while(componentStr[i] != ',' && componentStr[i] != ')') i++;
        }

    return comp;
}

Component cloneValuesComponent(Component component){
    Component clone = createComponent(component->symbol);

    for(int i = 0; i < component->cantParameters; i++)
        componentAddValue(clone, *(double*)component->parameters[i]);

    return clone;
}

void freeValuesComponent(void* component){
    if(component != NULL){
        Component comp = component;
        for(int i = 0; i < comp->cantParameters; i++)
            free(comp->parameters[i]);
        free(component);
    }
}