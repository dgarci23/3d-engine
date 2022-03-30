/*
 * graphics.cpp
 *
 *  Created on: 03/25/2022
 *      Author: david
 */


/*
 * graphics.c
 *
 *  Created on: 01/13/2022
 *      Author: david
 */

#include "graphics.h"
#include <unistd.h>
#include <cstdio>
#include <algorithm>

/***************************************************************
Function Name: waitSwap
Input Arguments: 0 or 1
Desc: Waits until the swap value from the FPGA is not i.
***************************************************************/
/*void waitSwap(int i){
    bool swap = i;
    while (swap == i){
    	swap = IORD_ALTERA_AVALON_PIO_DATA(SWAP_BASE);
    }
    return;
}*/

/***************************************************************
Point functions:
* setPoint: sets the point value in memory.
* drawPoint: draws the point in the screen.
***************************************************************/
void setPoint (Point a, int color) {

  if ((a.x < 0) || (a.x > 319) || (a.y < 0) || (a.y > 239)) return;


  IOWR_ALTERA_AVALON_PIO_DATA(DIN_BASE, color);
  IOWR_ALTERA_AVALON_PIO_DATA(WADDR_BASE, (int)a.y + (int)240*a.x);
  IOWR_ALTERA_AVALON_PIO_DATA(BB_WE_BASE, 1);
  IOWR_ALTERA_AVALON_PIO_DATA(BB_WE_BASE, 0);

}

void drawPoint(Point a, int color){
	waitSwap(1);
	IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 0);
	setPoint(a, color);
	IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 1);
	waitSwap(0);
	IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 0);
}

Point drawPoint(float x, float y, float z, int color){
	Point a = {x, y, z};

	drawPoint(a, color);

	return a;
}

/***************************************************************
Line functions:
* setLine: sets the line value in memory.
* drawLine: draws the line in the screen.
***************************************************************/
void setLine (Line l, int color) {
  Point a = {(int)l.a.x, (int)l.a.y};
  Point b = {(int)l.b.x, (int)l.b.y};
  int dx = abs(b.x-a.x), sx = a.x<b.x ? 1 : -1;
  int dy = abs(b.y-a.y), sy = a.y<b.y ? 1 : -1;
  int err = (dx>dy ? dx : -dy)/2, e2;

  for(;;){
	setPoint(a, color);
	if (a.x==b.x && a.y==b.y) break;
	e2 = err;
	if (e2 >-dx) { err -= dy; a.x += sx; }
	if (e2 < dy) { err += dx; a.y += sy; }
  }
}

Line drawLine (Point a, Point b, int color){

	Line l = {a, b};

	drawLine(l, color);

    return l;
}

void drawLine (Line l, int color) {
    waitSwap(1);
	IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 0);
	setLine(l, color);
    IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 1);
    waitSwap(0);
    IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 0);
}


/***************************************************************
Triangle functions:
* setTriangle: sets the triangle value in memory.
* drawTriangle: draws the triangle in the screen.
***************************************************************/
void setTriangle(Triangle t, int color) {
	Line l1 = {t.p[0], t.p[1]};
	Line l2 = {t.p[1], t.p[2]};
	Line l3 = {t.p[2], t.p[0]};


	setLine(l1, color);
	setLine(l2, color);
	setLine(l3, color);
}

Triangle drawTriangle (Point a, Point b, Point c, int color) {

	Triangle t = {a, b, c};

	drawTriangle(t, color);

	return t;
}

void drawTriangle(Triangle t, int color){

	waitSwap(1);
	IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 0);
	setTriangle(t, color);
    IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 1);
    waitSwap(0);
    IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 0);

}

Triangle setFillTriangle(Point a, Point b, Point c, int color){
	Triangle t = {a, b, c, color};

	setFillTriangle(t);

	return t;
}

void setFillTriangle(Triangle t) {
		int x1 = (int)t.p[0].x; int y1 = (int)t.p[0].y;
		int x2 = (int)t.p[1].x; int y2 = (int)t.p[1].y;
		int x3 = (int)t.p[2].x; int y3 = (int)t.p[2].y;

		auto SWAP = [](int &x, int &y) { int t = x; x = y; y = t; };
		auto drawline = [&](int sx, int ex, int ny) { for (int i = sx; i <= ex; i++) setPoint({(float)i, (float)ny, 0.0f}, t.color); };

		int t1x, t2x, y, minx, maxx, t1xp, t2xp;
		bool changed1 = false;
		bool changed2 = false;
		int signx1, signx2, dx1, dy1, dx2, dy2;
		int e1, e2;
		// Sort vertices
		if (y1>y2) { SWAP(y1, y2); SWAP(x1, x2); }
		if (y1>y3) { SWAP(y1, y3); SWAP(x1, x3); }
		if (y2>y3) { SWAP(y2, y3); SWAP(x2, x3); }

		t1x = t2x = x1; y = y1;   // Starting points
		dx1 = (int)(x2 - x1); if (dx1<0) { dx1 = -dx1; signx1 = -1; }
		else signx1 = 1;
		dy1 = (int)(y2 - y1);

		dx2 = (int)(x3 - x1); if (dx2<0) { dx2 = -dx2; signx2 = -1; }
		else signx2 = 1;
		dy2 = (int)(y3 - y1);

		if (dy1 > dx1) {   // swap values
			SWAP(dx1, dy1);
			changed1 = true;
		}
		if (dy2 > dx2) {   // swap values
			SWAP(dy2, dx2);
			changed2 = true;
		}

		e2 = (int)(dx2 >> 1);
		// Flat top, just process the second half
		if (y1 == y2) goto next;
		e1 = (int)(dx1 >> 1);

		for (int i = 0; i < dx1;) {
			t1xp = 0; t2xp = 0;
			if (t1x<t2x) { minx = t1x; maxx = t2x; }
			else { minx = t2x; maxx = t1x; }
			// process first line until y value is about to change
			while (i<dx1) {
				i++;
				e1 += dy1;
				while (e1 >= dx1) {
					e1 -= dx1;
					if (changed1) t1xp = signx1;//t1x += signx1;
					else          goto next1;
				}
				if (changed1) break;
				else t1x += signx1;
			}
			// Move line
		next1:
			// process second line until y value is about to change
			while (1) {
				e2 += dy2;
				while (e2 >= dx2) {
					e2 -= dx2;
					if (changed2) t2xp = signx2;//t2x += signx2;
					else          goto next2;
				}
				if (changed2)     break;
				else              t2x += signx2;
			}
		next2:
			if (minx>t1x) minx = t1x;
			if (minx>t2x) minx = t2x;
			if (maxx<t1x) maxx = t1x;
			if (maxx<t2x) maxx = t2x;
			drawline(minx, maxx, y);    // Draw line from min to max points found on the y
										 // Now increase y
			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y == y2) break;

		}
	next:
		// Second half
		dx1 = (int)(x3 - x2); if (dx1<0) { dx1 = -dx1; signx1 = -1; }
		else signx1 = 1;
		dy1 = (int)(y3 - y2);
		t1x = x2;

		if (dy1 > dx1) {   // swap values
			SWAP(dy1, dx1);
			changed1 = true;
		}
		else changed1 = false;

		e1 = (int)(dx1 >> 1);

		for (int i = 0; i <= dx1; i++) {
			t1xp = 0; t2xp = 0;
			if (t1x<t2x) { minx = t1x; maxx = t2x; }
			else { minx = t2x; maxx = t1x; }
			// process first line until y value is about to change
			while (i<dx1) {
				e1 += dy1;
				while (e1 >= dx1) {
					e1 -= dx1;
					if (changed1) { t1xp = signx1; break; }//t1x += signx1;
					else          goto next3;
				}
				if (changed1) break;
				else   	   	  t1x += signx1;
				if (i<dx1) i++;
			}
		next3:
			// process second line until y value is about to change
			while (t2x != x3) {
				e2 += dy2;
				while (e2 >= dx2) {
					e2 -= dx2;
					if (changed2) t2xp = signx2;
					else          goto next4;
				}
				if (changed2)     break;
				else              t2x += signx2;
			}
		next4:

			if (minx>t1x) minx = t1x;
			if (minx>t2x) minx = t2x;
			if (maxx<t1x) maxx = t1x;
			if (maxx<t2x) maxx = t2x;
			drawline(minx, maxx, y);
			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y>y3) return;
		}
}

void fillTriangle(Triangle t) {
	waitSwap(1);
	IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 0);
	setFillTriangle(t);
	IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 1);
	waitSwap(0);
	IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 0);
}

void setDeleteTriangle(Triangle &t){
	t.color = 0;
	setFillTriangle(t);
}

void assignColor(Triangle &t, char color) {
	t.color = color;
}

/***************************************************************
Square functions:
* setLine: sets the line value in memory.
* drawLine: draws the line in the screen.
***************************************************************/

void fillSquare(int x0, int x1, int y0, int y1, int color) {
	waitSwap(1);
	IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 0);
	for (int i = x0; i < x1; i++) {
		for (int j = y0; j < y1; j++) {
			setPoint({(float)i, (float)j, 0.0f}, color);
		}
	}
    IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 1);
    waitSwap(0);
    IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 0);
}

void fillScreen(int color) {
	fillSquare(0, 320, 0, 240, color);
}

void drawBackground(char background[320][240]){
	waitSwap(1);
	IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 0);
	for (int x = 0; x < 320; x++){
		for (int y = 0; y < 240; y++){
			setPoint({(float)x,(float)y, 0.0f},background[x][y]);
		}
	}
    IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 1);
    waitSwap(0);
    IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 0);
}

void sortMesh(Mesh &m) {
	sort(m.tris.begin(), m.tris.end(), [](Triangle &t1, Triangle &t2){
		float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z)/3.0f;
		float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z)/3.0f;
		return z1 > z2;
	});
}

void setMesh(Mesh &m){
  for (auto tri : m.tris){
	setFillTriangle(tri);
  }
}

void setDeleteMesh(Mesh &m) {
  while (!(m.tris.empty())){
	setDeleteTriangle(m.tris.back());// There should be a method to set a triangle to background
	m.tris.pop_back();
  }
}

void waitSwap(int i){
    bool swap = i;
    while (swap == i){
    	swap = IORD_ALTERA_AVALON_PIO_DATA(SWAP_BASE);
    }
    return;
}


