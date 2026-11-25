#ifndef LSYSTEM_H
#define LSYSTEM_H

#define LSYSTEM_MAX_RULES 32

#include "rule.h"
#include <stdio.h>

typedef struct{
    Rule rules[LSYSTEM_MAX_RULES];
    List iterationComponents;
    int cantRules;
}lsystemT;

typedef lsystemT* Lsystem;

Lsystem createLsystem();
void lsystemAddRule(Lsystem lsystem, Rule rule);
void lsystemSetComponents(Lsystem lsystem, List components);
void lsystemIterate(Lsystem lsystem);
void lsystemIterationToString(char* iterationStr, Lsystem lsystem, int numStrTam);
List lsystemStringToComponentList(char* iterationStr);


/*
F, G move drawing
f, g move (TODO)
O draw sphere (TODO)
 
+ yaw left
- yaw right
& pitch down
^ pitch up
/ roll left
\ roll right
| yaw 180 deg (TODO)

[ push state
] pop state

# increase line width (or set)
! decrease line width (or set)

; increase color map (or set)
, decrease color map (or set)

*/

#endif