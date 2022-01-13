#include "transforms.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

void MultiplyMatrixVector(Point &i, Point &o, mat4x4 &m){

	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

	if (w != 0.0f)
	{
		o.x /= w; o.y /= w; o.z /= w;
	}

}

void MultiplyMatrixTriangle(Triangle &i, Triangle &o, mat4x4 &m){
	MultiplyMatrixVector(i.p[0], o.p[0], m);
	MultiplyMatrixVector(i.p[1], o.p[1], m);
	MultiplyMatrixVector(i.p[2], o.p[2], m);
}

Point addPoint(Point &a, Point &b){
	Point c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return c;
}

Point subPoint(Point &a, Point &b){
	Point c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return c;
}

Point prodPoint(Point &a, Point &b){
	Point c;
	c.x = a.x*b.x;
	c.y = a.y*b.y;
	c.z = a.z*b.z;
	return c;
}

void getmatProj(mat4x4 &matProj){
	float fNear = 0.1f;
	float fFar = 1000.0f;
	float fFov = 90.0f;
	float fAspectRatio = (float)240 / (float)320;
	float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

	matProj.m[0][0] = fAspectRatio * fFovRad;
	matProj.m[1][1] = fFovRad;
	matProj.m[2][2] = fFar / (fFar - fNear);
	matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	matProj.m[2][3] = 1.0f;
	matProj.m[3][3] = 0.0f;
}

void Project(Point &i, Point &o){

	mat4x4 matProj;

	getmatProj(matProj);

	MultiplyMatrixVector(i,o,matProj);

}
void Project(Triangle &i, Triangle &o){

	mat4x4 matProj;

	getmatProj(matProj);

	MultiplyMatrixVector(i.p[0],o.p[0],matProj);
	MultiplyMatrixVector(i.p[1],o.p[1],matProj);
	MultiplyMatrixVector(i.p[2],o.p[2],matProj);

}

void Normalize(Point &i){
	float l = sqrtf(i.x*i.x + i.y*i.y + i.z*i.z);
	i.x /= l; i.y /= l; i.z /= l;
}

float dp (Point a, Point b){
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

Point cp (Point a, Point b){
	float x = a.y * b.z - a.z * b.y;
	float y = a.z * b.x - a.x * b.z;
	float z = a.x * b.y - a.y * b.x;

	return {x, y, z};
}

void xRotate(Point &i, Point &o, float angle){

	mat4x4 matRotX;

	matRotX.m[0][0] = 1;
	matRotX.m[1][1] = cosf(angle * (3.14159f/180.0f));
	matRotX.m[1][2] = sinf(angle * (3.14159f/180.0f));
	matRotX.m[2][1] = -sinf(angle * (3.14159f/180.0f));
	matRotX.m[2][2] = cosf(angle * (3.14159f/180.0f));
	matRotX.m[3][3] = 1;

	MultiplyMatrixVector(i, o, matRotX);

}

mat4x4 getMatRotX(float angle){

	mat4x4 matRotX;

	matRotX.m[0][0] = 1;
	matRotX.m[1][1] = cosf(angle * (3.14159f/180.0f));
	matRotX.m[1][2] = sinf(angle * (3.14159f/180.0f));
	matRotX.m[2][1] = -sinf(angle * (3.14159f/180.0f));
	matRotX.m[2][2] = cosf(angle * (3.14159f/180.0f));
	matRotX.m[3][3] = 1;

	return matRotX;
}


void yRotate(Point &i, Point &o, float angle){
	mat4x4 matRotY;

	matRotY.m[0][0] = cosf(angle * (3.14159f/180.0f));
	matRotY.m[0][2] = -sinf(angle * (3.14159f/180.0f));
	matRotY.m[1][1] = 1;
	matRotY.m[2][0] = sinf(angle * (3.14159f/180.0f));
	matRotY.m[2][2] = cosf(angle * (3.14159f/180.0f));
	matRotY.m[3][3] = 1;

	MultiplyMatrixVector(i, o, matRotY);
}

mat4x4 getMatRotY(float angle){
	mat4x4 matRotY;

	matRotY.m[0][0] = cosf(angle * (3.14159f/180.0f));
	matRotY.m[0][2] = -sinf(angle * (3.14159f/180.0f));
	matRotY.m[1][1] = 1;
	matRotY.m[2][0] = sinf(angle * (3.14159f/180.0f));
	matRotY.m[2][2] = cosf(angle * (3.14159f/180.0f));
	matRotY.m[3][3] = 1;

	return matRotY;
}

void zRotate(Point &i, Point &o, float angle){

	mat4x4 matRotZ;

	matRotZ.m[0][0] = cosf(angle * (3.14159f/180.0f));
	matRotZ.m[0][1] = sinf(angle * (3.14159f/180.0f));
	matRotZ.m[1][0] = -sinf(angle * (3.14159f/180.0f));
	matRotZ.m[1][1] = cosf(angle * (3.14159f/180.0f));
	matRotZ.m[2][2] = 1;
	matRotZ.m[3][3] = 1;

	MultiplyMatrixVector(i, o, matRotZ);
}

mat4x4 getMatRotZ(float angle){

	mat4x4 matRotZ;

	matRotZ.m[0][0] = cosf(angle * (3.14159f/180.0f));
	matRotZ.m[0][1] = sinf(angle * (3.14159f/180.0f));
	matRotZ.m[1][0] = -sinf(angle * (3.14159f/180.0f));
	matRotZ.m[1][1] = cosf(angle * (3.14159f/180.0f));
	matRotZ.m[2][2] = 1;
	matRotZ.m[3][3] = 1;

	return matRotZ;
}

void xRotate(Triangle &i, Triangle &o, float angle){
	mat4x4 matRotX;

	matRotX.m[0][0] = 1;
	matRotX.m[1][1] = cosf(angle * (3.14159f/180.0f));
	matRotX.m[1][2] = sinf(angle * (3.14159f/180.0f));
	matRotX.m[2][1] = -sinf(angle * (3.14159f/180.0f));
	matRotX.m[2][2] = cosf(angle * (3.14159f/180.0f));
	matRotX.m[3][3] = 1;

	MultiplyMatrixVector(i.p[0], o.p[0], matRotX);
	MultiplyMatrixVector(i.p[1], o.p[1], matRotX);
	MultiplyMatrixVector(i.p[2], o.p[2], matRotX);
}
void yRotate(Triangle &i, Triangle &o, float angle){
	mat4x4 matRotY;

	matRotY.m[0][0] = cosf(angle * (3.14159f/180.0f));
	matRotY.m[0][2] = -sinf(angle * (3.14159f/180.0f));
	matRotY.m[1][1] = 1;
	matRotY.m[2][0] = sinf(angle * (3.14159f/180.0f));
	matRotY.m[2][2] = cosf(angle * (3.14159f/180.0f));
	matRotY.m[3][3] = 1;

	MultiplyMatrixVector(i.p[0], o.p[0], matRotY);
	MultiplyMatrixVector(i.p[1], o.p[1], matRotY);
	MultiplyMatrixVector(i.p[2], o.p[2], matRotY);
}
void zRotate(Triangle &i, Triangle &o, float angle){
	mat4x4 matRotZ;

	matRotZ.m[0][0]   = cosf(angle * (3.14159f/180.0f));
	matRotZ.m[0][1] = sinf(angle * (3.14159f/180.0f));
	matRotZ.m[1][0] = -sinf(angle * (3.14159f/180.0f));
	matRotZ.m[1][1] = cosf(angle * (3.14159f/180.0f));
	matRotZ.m[2][2] = 1;
	matRotZ.m[3][3] = 1;

	MultiplyMatrixVector(i.p[0], o.p[0], matRotZ);
	MultiplyMatrixVector(i.p[1], o.p[1], matRotZ);
	MultiplyMatrixVector(i.p[2], o.p[2], matRotZ);
}

void ScaleIntoView(Triangle &t){
	t.p[0].x += 1.0f; t.p[0].y += 1.0f;
	t.p[1].x += 1.0f; t.p[1].y += 1.0f;
	t.p[2].x += 1.0f; t.p[2].y += 1.0f;
	t.p[0].x *= 0.5f * (float)SCREEN_WIDTH;
	t.p[0].y *= 0.5f * (float)SCREEN_HEIGHT;
	t.p[1].x *= 0.5f * (float)SCREEN_WIDTH;
	t.p[1].y *= 0.5f * (float)SCREEN_HEIGHT;
	t.p[2].x *= 0.5f * (float)SCREEN_WIDTH;
	t.p[2].y *= 0.5f * (float)SCREEN_HEIGHT;
}

void getCube(Mesh &meshCube){
	meshCube.tris = {

			// SOUTH
			{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

			// EAST
			{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
			{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

			// NORTH
			{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
			{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

			// WEST
			{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

			// TOP
			{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
			{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

			// BOTTOM
			{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
			{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },

	};
}

mat4x4 MultiplyMatrixMatrix(mat4x4 &m1, mat4x4 &m2){

	mat4x4 matrix;
	for (int c =0; c < 4; c++){
		for (int r = 0; r < 4; r++){
			matrix.m[r][c] = m1.m[r][0] * m2.m[0][c] + m1.m[r][1] * m2.m[1][c] + m1.m[r][2] * m2.m[2][c] + m1.m[r][3] * m2.m[3][c];
		}
	}

	return matrix;

}

mat4x4 getIdentityMatrix() {

	mat4x4 matrix;
	for (int i = 0; i < 4; i++) {
		matrix.m[i][i] = 1;
	}

	return matrix;
}

mat4x4 getTranslationMatrix(float x, float y, float z){
	mat4x4 matrix;

	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	matrix.m[3][0] = x;
	matrix.m[3][1] = y;
	matrix.m[3][2] = z;
	return matrix;
}

mat4x4 getWorldMatrix(float angle) {
	mat4x4 matRotZ, matRotX, matTrans, matWorld;

	matRotX = getMatRotX(0.7f* angle);
	matRotZ = getMatRotZ(angle * 0.9f);

	matWorld = getIdentityMatrix();
	matTrans = getTranslationMatrix(angle*0.00f, 0.0f, 6.0f);

	matWorld = MultiplyMatrixMatrix(matRotZ, matRotX);
	matWorld = MultiplyMatrixMatrix(matWorld, matTrans);

	return matWorld;
}


