/*
 * main.c
 *
 *  Created on: 11/25/2021
 *      Author: david
 */



#include <unistd.h>

#include "../3d-engine_bsp/system.h"


#include "graphics.h"
#include "transforms.h"

#include "load.h"

#include <cstdio>


char getColor (float lum){
	return (char)(3.0f*lum+1.0f);
}


int main() {
	fillScreen(0);

	Mesh meshCube; // = LoadFromObjectFile();

	getCube(meshCube);

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
}
