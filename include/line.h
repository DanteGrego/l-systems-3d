#ifndef LINE_H
#define LINE_H

#include <raylib.h>
#include "vector3.h"
#include "list.h"

typedef struct{
    vector3 p1, p2;
    float colorHue, width;
}lineT;

void drawLine(lineT line);
void drawLineList(List lineList);

#endif