#ifndef TURTLE_H
#define TURTLE_H

#include "vector3.h"
#include "component.h"
#include "stack.h"
#include "list.h"
#include "line.h"

#define TURTLE_DEFAULT_SPEED 25
#define TURTLE_DEFAULT_TURN_YAW 30
#define TURTLE_DEFAULT_TURN_PITCH 30
#define TURTLE_DEFAULT_TURN_ROLL 30
#define TURTLE_DEFAULT_LINE_W_CHANGE 0.1
#define TURTLE_DEFAULT_HUE_CHANGE 10

typedef struct {
	vector3 position;
	vector3 direction;
	double lineWidth;
	int lineColorHue;
}TurtleProperties;

typedef struct{
	vector3 position;
	vector3 direction;
	double lineWidth;
	int lineColorHue;
	Stack stateStack;
}turtleT;

typedef turtleT* Turtle;

Turtle createTurtle(vector3 position, vector3 direction, double lineWidth, int lineColorHue);
void turtleMoveForward(Turtle turtle, double amount);
void turtleMoveForwardDrawing(Turtle turtle, double amount, List* lineList);
void turtleTurnPitch(Turtle turtle, float amount);
void turtleTurnRoll(Turtle turtle, float amount);
void turtleTurnYaw(Turtle turtle, float amount);
void turtlePushState(Turtle turtle);
void turtlePopState(Turtle turtle);
void turtleSetLineWidth(Turtle turtle, double width);
void turtleIncrementLineWidth(Turtle turtle, double widthChange);
void turtleSetLineColorHue(Turtle turtle, int hue);
void turtleIncrementLineColorHue(Turtle turtle, int hueChange);
void turtleDrawCircle(Turtle turtle, double radius);
void turtleFollowInstruction(Turtle turtle, Component component, List* lineList);
List turtleFollowInstructionList(Turtle turtle, List instructionsList);

#endif