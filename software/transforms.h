/*
 * transforms.h
 *
 *  Created on: 11/23/2021
 *      Author: david
 */

#ifndef TRANSFORMS_H_
#define TRANSFORMS_H_

#include <cmath>

#include "graphics.h"

struct mat4x4 {
	float m[4][4] = {0.0f};
};

void MultiplyMatrixVector(Point &i, Point &o, mat4x4 &m);

void MultiplyMatrixTriangle(Triangle &i, Triangle &o, mat4x4 &m);

Point addPoint(Point &a, Point &b);
Point subPoint(Point &a, Point &b);
Point prodPoint(Point &a, Point &b);

void Normalize(Point &i);
float dp (Point a, Point b);
Point cp (Point a, Point b);

void getmatProj(mat4x4 &matProj);

void Project(Point &i, Point &o);
void Project(Triangle &i, Triangle &o);

void xRotate(Point &i, Point &o, float angle);
void yRotate(Point &i, Point &o, float angle);
void zRotate(Point &i, Point &o, float angle);

void xRotate(Triangle &i, Triangle &o, float angle);
void yRotate(Triangle &i, Triangle &o, float angle);
void zRotate(Triangle &i, Triangle &o, float angle);

mat4x4 getMatRotX(float angle);
mat4x4 getMatRotY(float angle);
mat4x4 getMatRotZ(float angle);

void ScaleIntoView(Triangle &t);

void getCube(Mesh &meshCube);

mat4x4 MultiplyMatrixMatrix(mat4x4 &a, mat4x4 &b);

mat4x4 getIdentityMatrix();

mat4x4 getTranslationMatrix(float x, float y, float z);

mat4x4 getWorldMatrix(float angle);

#endif /* TRANSFORMS_H_ */
