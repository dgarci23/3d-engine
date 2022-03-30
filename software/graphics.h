/*
 * graphics.h
 *
 *  Created on: 11/22/2021
 *      Author: david
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_


#include <cmath>
#include <vector>
#include "../3d-engine_bsp/drivers/inc/altera_avalon_pio_regs.h"
#include "../3d-engine_bsp/system.h"


struct Point {
	float x = 0;
	float y = 0;
	float z = 0;
};

struct Line {
	Point a;
	Point b;
};

struct Triangle {
	Point p[3];

	char color;
};

struct Mesh {
	std::vector<Triangle> tris;
};


void waitSwap(int i);

void setPoint (Point a, int color);
void drawPoint(Point a, int color);
Point drawPoint(float x, float y, float z, int color);

void setLine (Line l, int color);
void drawLine (Line l, int color);
Line drawLine (Point a, Point b, int color);

void setTriangle (Triangle t, int color);
Triangle drawTriangle (Point a, Point b, Point c, int color);
void drawTriangle(Triangle t, int color);
void fillTriangle(Triangle t, int color);
void setFillTriangle(Triangle t);
Triangle setFillTriangle(Point a, Point b, Point c, int color);
void setDeleteTriangle(Triangle &t);
void assignColor(Triangle &t, char color);

void fillSquare(int x0, int x1, int y0, int y1, int color);
void fillScreen(int color);
void drawBackground(char background[320][240]);

void sortMesh(Mesh &m);
void setMesh(Mesh &m);
void setDeleteMesh(Mesh &m);


#endif /* GRAPHICS_H_ */


