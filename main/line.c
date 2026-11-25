#include "../include/line.h"

Vector3 vector3TransformType(vector3 v){
    return (Vector3){v.x, v.y, v.z};
}

void drawLine(lineT line){
    DrawCapsule(vector3TransformType(line.p1), vector3TransformType(line.p2), line.width/2.0, 10, 10, ColorFromHSV(line.colorHue, 1, 1));
}

void drawLineList(List lineList){
    for(listNode* nodeAct = lineList; nodeAct != NULL; nodeAct = nodeAct->sig)
        drawLine(*(lineT*)nodeAct->value);
}