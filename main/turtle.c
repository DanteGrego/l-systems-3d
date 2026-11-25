#include "../include/turtle.h"

Turtle createTurtle(vector3 position, vector3 direction, double lineWidth, int lineColorHue) {
	Turtle turtle = (Turtle)malloc(sizeof(turtleT));
	turtle->position = position;
	turtle->direction = direction;
	turtle->lineWidth = lineWidth;
	turtle->lineColorHue = lineColorHue;
	return turtle;
}

void turtleMoveForward(Turtle turtle, double amount) {
	turtle->position = vector3Add(turtle->position, vector3MulK(turtle->direction, amount));
}

void turtleMoveForwardDrawing(Turtle turtle, double amount, List* lineList) {
	vector3 prevPosition = turtle->position;
	turtleMoveForward(turtle, amount);

	lineT* line = (lineT*)malloc(sizeof(lineT));
	line->p1 = prevPosition;
	line->p2 = turtle->position;
	line->width = turtle->lineWidth;
	line->colorHue = turtle->lineColorHue;

	listAppend(lineList, createListNode(line));
}

void turtleTurnPitch(Turtle turtle, float amount){
	turtle->direction = vector3Pitch(turtle->direction, amount*3.141592/180);
}

void turtleTurnRoll(Turtle turtle, float amount){
	turtle->direction = vector3Roll(turtle->direction, amount*3.141592/180);
}

void turtleTurnYaw(Turtle turtle, float amount){
	turtle->direction = vector3Yaw(turtle->direction, amount*3.141592/180);
}

void turtlePushState(Turtle turtle) {
	TurtleProperties* props = (TurtleProperties*)malloc(sizeof(TurtleProperties));
	props->position = turtle->position;
	props->direction = turtle->direction;
	props->lineWidth = turtle->lineWidth;
	props->lineColorHue = turtle->lineColorHue;
	stackPush(&turtle->stateStack, props);
}

void turtlePopState(Turtle turtle) {
	TurtleProperties* props = (TurtleProperties*)stackPop(&turtle->stateStack);
	turtle->position = props->position;
	turtle->direction = props->direction;
	turtle->lineWidth = props->lineWidth;
	turtle->lineColorHue = props->lineColorHue;
	free(props);
}

void turtleSetLineWidth(Turtle turtle, double width) {
	turtle->lineWidth = width;
}

void turtleIncrementLineWidth(Turtle turtle, double widthChange) {
	turtle->lineWidth += widthChange;
}

void turtleSetLineColorHue(Turtle turtle, int hue){
	turtle->lineColorHue = hue;
}

void turtleIncrementLineColorHue(Turtle turtle, int hueChange){
	turtle->lineColorHue += hueChange;
}

void turtleDrawCircle(Turtle turtle, double radius){
	
}

void turtleFollowInstruction(Turtle turtle, Component component, List* lineList){
	double value;
	switch(component->symbol){
		case 'F':
			if(component->cantParameters > 0)
				value = *(double*)(component->parameters[0]);
			else
				value = TURTLE_DEFAULT_SPEED;
			turtleMoveForwardDrawing(turtle, value, lineList);
			break;
		case 'G'://same as F
			if(component->cantParameters > 0)
				value = *(double*)(component->parameters[0]);
			else
				value = TURTLE_DEFAULT_SPEED;
			turtleMoveForwardDrawing(turtle, value, lineList);
			break;
		case '+':
			if(component->cantParameters > 0)
				value = *(double*)(component->parameters[0]);
			else
				value = TURTLE_DEFAULT_TURN_YAW;
			turtleTurnYaw(turtle, value);
			break;
		case '-':
			if(component->cantParameters > 0)
				value = *(double*)(component->parameters[0]);
			else
				value = TURTLE_DEFAULT_TURN_YAW;
			turtleTurnYaw(turtle, value);
			break;
		case '&':
			if(component->cantParameters > 0)
				value = *(double*)(component->parameters[0]);
			else
				value = TURTLE_DEFAULT_TURN_PITCH;
			turtleTurnPitch(turtle, -value);
			break;
		case '^':
			if(component->cantParameters > 0)
				value = *(double*)(component->parameters[0]);
			else
				value = TURTLE_DEFAULT_TURN_PITCH;
			turtleTurnPitch(turtle, value);//TODO quiza es al reves los signos con & y ^
			break;
		case '/':
			if(component->cantParameters > 0)
				value = *(double*)(component->parameters[0]);
			else
				value = TURTLE_DEFAULT_TURN_ROLL;
			turtleTurnRoll(turtle, -value);
			break;
		case '\\':
			if(component->cantParameters > 0)
				value = *(double*)(component->parameters[0]);
			else
				value = TURTLE_DEFAULT_TURN_ROLL;
			turtleTurnRoll(turtle, value);
			break;
		case '[':
			turtlePushState(turtle);
			break;
		case ']':
			turtlePopState(turtle);
			break;
		case '#':
			if(component->cantParameters > 0)
				turtleSetLineWidth(turtle, *(double*)component->parameters[0]);
			else
				turtleIncrementLineWidth(turtle, TURTLE_DEFAULT_LINE_W_CHANGE);
			break;
		case '!':
			if(component->cantParameters > 0)
				turtleSetLineWidth(turtle, *(double*)component->parameters[0]);
			else
				turtleIncrementLineWidth(turtle, -TURTLE_DEFAULT_LINE_W_CHANGE);
			break;
		case ';':
			if(component->cantParameters > 0)
				turtleSetLineColorHue(turtle, *(double*)component->parameters[0]);
			else
				turtleIncrementLineColorHue(turtle, TURTLE_DEFAULT_HUE_CHANGE);	
			break;	
		case ',':
			if(component->cantParameters > 0)
				turtleSetLineColorHue(turtle, *(double*)component->parameters[0]);
			else
				turtleIncrementLineColorHue(turtle, -TURTLE_DEFAULT_HUE_CHANGE);	
			break;	
		case 'O':
			turtleDrawCircle(turtle, *(double*)component->parameters[0]);
			break;
	}
}

List turtleFollowInstructionList(Turtle turtle, List instructionsList){
	List lineList;
	listInitialize(&lineList);

	for(listNode* node = instructionsList; node != NULL; node = node->sig)
		turtleFollowInstruction(turtle, node->value, &lineList);

	return lineList;
}