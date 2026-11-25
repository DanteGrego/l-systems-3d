#ifndef CONTROLLER_H
#define CONTROLLER_H

#define CAMERA_VELOCITY 2
#define CAMERA_SENSITIVITY 1
#define CAMERA_FOV 60

#include "line.h"
#include "lsystem.h"
#include "turtle.h"
#include <raylib.h>

typedef struct{
    Turtle turtle;
    Lsystem lsystem;
}controllerT;

typedef controllerT* Controller;

Controller createController();
void controllerLsystemSetAxiom(Controller controller, char* axiomStr);
void controllerLsystemAddRule(Controller controller, char* ruleStr);
void controllerLSystemIterate(Controller controller, int cantIterations, int debugPrinting);
void controllerTurtleInitialize(Controller controller, vector3 position, vector3 direction, float lineWidth, float lineColorHue);
void controllerTurtleDrawIteration(Controller controller, int windowWidth, int windowHeight);

#endif