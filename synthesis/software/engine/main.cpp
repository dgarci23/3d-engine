/*
 * main.cpp
 *
 *  Created on: 03/25/2022
 *      Author: david
 */



#include <unistd.h>

#include "../engine_bsp/system.h"


#include "graphics.h"
#include "transforms.h"

#include "load.h"

#include <cstdio>
#include <time.h>

int sign (Point p1, Point p2, Point p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

int inside_t (Triangle t, Point a){
    int d1, d2, d3;
    bool has_neg, has_pos;

    d1 = (a.x - t.p[1].x) * (t.p[0].y - t.p[1].y) - (t.p[0].x - t.p[1].x) * (a.y - t.p[1].y);
    //d1 = sign(a, t.p[0], t.p[1]);
    d2 = sign(a, t.p[1], t.p[2]);
    d3 = sign(a, t.p[2], t.p[0]);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

char getColor (float lum){
	return (char)(3.0f*lum+1.0f);
}


int main() {

	fillScreen(0);

	Mesh meshCube = LoadFromObjectFile();

	float fTheta = 0;
	float fElapsedTime = 5;

	Mesh mainMesh, trianglesToRaster;

	Point camera;

	while(1){

		fTheta += 1.0f * fElapsedTime;

		mat4x4 matWorld = getWorldMatrix(fTheta);

		waitSwap(1);
		IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 0);
		setDeleteMesh(mainMesh);

		// Draw Triangles

		for (auto tri : meshCube.tris)
		{
			Triangle triProjected, triTransformed, triRotatedZ, triRotatedZX;

			MultiplyMatrixTriangle(tri, triTransformed, matWorld);


			Point normal, line1, line2;
			line1 = subPoint(triTransformed.p[1], triTransformed.p[0]);
			line2 = subPoint(triTransformed.p[2], triTransformed.p[0]);

			normal = cp(line1, line2);
			Normalize(normal);

			if(dp(normal, subPoint(triTransformed.p[0], camera)) < 0.0f){


				Point light_direction = {0.0f, 0.0f, -1.0f};
				Normalize(light_direction);

				float dp_l = dp(light_direction, normal);

				// Project triangles from 3D --> 2D
				Project(triTransformed, triProjected);

				// Scale into view
				ScaleIntoView(triProjected);

				assignColor(triProjected, getColor(dp_l));

				// Rasterize triangle
				mainMesh.tris.push_back(triProjected);
			}

		}

		sortMesh(mainMesh);

		setMesh(mainMesh);

	    IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 1);
	    waitSwap(0);
	    IOWR_ALTERA_AVALON_PIO_DATA(DONE_BASE, 0);
	}

	while (1) {}
}


