#ifndef VECTOR3_H
#define VECTOR3_H

#include "math.h"

typedef struct {
	double x, y, z;
}vector3;

vector3 createVector3(double x, double y, double z);
vector3 vector3Add(vector3 a, vector3 b);
vector3 vector3Sub(vector3 a, vector3 b);
vector3 vector3MulK(vector3 v, double k);
double vector3Mag(vector3 v);
vector3 vector3Pitch(vector3 v, double ang);
vector3 vector3Roll(vector3 v, double ang);
vector3 vector3Yaw(vector3 v, double ang);
vector3 vector3SetMag(vector3 v, double mag);
double vector3AngleXY(vector3 v);

#endif