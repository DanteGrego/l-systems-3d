#include "../include/vector3.h"

vector3 createVector3(double x, double y, double z) {
	vector3 v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

vector3 vector3Add(vector3 a, vector3 b) {
	vector3 sum;
	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	sum.z = a.z + b.z;
	return sum;
}

vector3 vector3Sub(vector3 a, vector3 b) {
	vector3 sub;
	sub.x = a.x - b.x;
	sub.y = a.y - b.y;
	sub.z = a.z - b.z;
	return sub;
}

vector3 vector3MulK(vector3 v, double k) {
	vector3 mul;
	mul.x = v.x * k;
	mul.y = v.y * k;
	mul.z = v.z * k;
	return mul;
}

double vector3Mag(vector3 v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vector3 vector3Pitch(vector3 v, double ang){
	vector3 rot;
	rot.x = v.x*cosf(ang) - v.y*sinf(ang);
	rot.y = v.x*sinf(ang) + v.y*cosf(ang);
	rot.z = v.z;
	return rot;
}

vector3 vector3Roll(vector3 v, double ang){
	vector3 rot;
	rot.x = v.x;
	rot.y = v.y*cosf(ang) - v.z*sinf(ang);
	rot.z = v.y*sinf(ang) + v.z*cosf(ang);
	return rot;
}

vector3 vector3Yaw(vector3 v, double ang){
	vector3 rot;
	rot.x = v.x*cosf(ang) + v.z*sinf(ang);
	rot.y = v.y;
	rot.z = -v.x*sinf(ang) + v.z*cosf(ang);
	return rot;
}

vector3 vector3SetMag(vector3 v, double mag) {
	return vector3MulK(v, mag / vector3Mag(v));
}

double vector3AngleXY(vector3 v) {
	return atan(v.y / v.x);
}