#ifndef __PRIMITIVE_MESHES_H__
#define __PRIMITIVE_MESHES_H__

#include "Globals.h"
#include "Application.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "glew/include/GL/glew.h"

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

class CubePrimitive
{
public:
	CubePrimitive() {};
	~CubePrimitive() { };

	void DrawDirectMode()
	{
		glBegin(GL_QUADS); // Begin drawing the color cube with 6 quads
		// Top face (y = 1.0f)
		// Define vertices in counter-clockwise (CCW) order with normal pointing out
		glColor3f(0.0f, 2.0f, 0.0f);     // Top: Green
		glVertex3f(1.0f, 2.0f, -1.0f);
		glVertex3f(-1.0f, 2.0f, -1.0f);
		glVertex3f(-1.0f, 2.0f, 1.0f);
		glVertex3f(1.0f, 2.0f, 1.0f);

		// Bottom face (y = -1.0f)
		glColor3f(1.0f, 0.5f, 0.0f);     // Bottom: Orange
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);

		// Front face  (z = 1.0f)
		glColor3f(1.0f, 0.0f, 0.0f);     // Front: Red
		glVertex3f(1.0f, 2.0f, 1.0f);
		glVertex3f(-1.0f, 2.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);

		// Back face (z = -1.0f)
		glColor3f(1.0f, 1.0f, 0.0f);     // Back: Yellow
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, 2.0f, -1.0f);
		glVertex3f(1.0f, 2.0f, -1.0f);

		// Left face (x = -1.0f)
		glColor3f(0.0f, 0.0f, 1.0f);     // Left: Blue
		glVertex3f(-1.0f, 2.0f, 1.0f);
		glVertex3f(-1.0f, 2.0f, -1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);

		// Right face (x = 1.0f)
		glColor3f(1.0f, 0.0f, 1.0f);     // Right: Magenta
		glVertex3f(1.0f, 2.0f, -1.0f);
		glVertex3f(1.0f, 2.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);

		glEnd();  // End of drawing color-cube
	}



private:
};

class PyramidPrimitive
{
public:
	PyramidPrimitive() {};
	~PyramidPrimitive() { };

	void DrawDirectMode()
	{
		glBegin(GL_TRIANGLES); // Begin drawing the color cube with 6 quads
		


		glColor3f(1.0f, 0.0f, 0.0f); 
		glVertex3f(0.0f, 2.0f, 0.0f);   
		glVertex3f(-1.0f, 0.0f, 1.0f);   
		glVertex3f(1.0f, 0.0f, 1.0f);   
	  //Triangle 2
		glColor3f(0.0f, 1.0f, 0.0f); 
		glVertex3f(0.0f, 2.0f, 0.0f);   
		glVertex3f(1.0f, 0.0f, 1.0f);   
		glVertex3f(1.0f, 0.0f, -1.0f);   
	  //Triangle 3
		glColor3f(0.0f, 0.0f, 1.0f); 
		glVertex3f(0.0f, 2.0f, 0.0f);   
		glVertex3f(1.0f, 0.0f, -1.0f);   
		glVertex3f(-1.0f, 0.0f, -1.0f);   
	  //Triangle 4
		glColor3f(1.0f, 0.0f, 0.5f); 
		glVertex3f(0.0f, 2.0f, 0.0f);   //V0(red)
		glVertex3f(-1.0f, 0.0f, -1.0f);   //V4(blue)
		glVertex3f(-1.0f, 0.0f, 1.0f);   //V1(green)
		glEnd();

		glBegin(GL_QUADS); // Begin drawing the color cube with 6 quads
		// Bottom face (y = -1.0f)
		glColor3f(1.0f, 0.5f, 0.0f);     // Bottom: Orange
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
	

		glEnd();  // End of drawing color-cube
	}



private:
};

class SpherePrimitive
{
public:

	SpherePrimitive() {};
	~SpherePrimitive() { };

	void DrawDirectMode()
	{
		double r = 1;
		int lats = 100;
		int longs = 100;

		for (int i = 0; i <= lats; i++) {
			double lat0 = M_PI * (-0.5 + (double)(i - 1) / lats);
			double z0 = sin(lat0);
			double zr0 = cos(lat0);

			double lat1 = M_PI * (-0.5 + (double)i / lats);
			double z1 = sin(lat1);
			double zr1 = cos(lat1);

			glBegin(GL_QUAD_STRIP);
			glColor3f(1.0f, 0.0f, 1.0f);     // Right: Magenta
			for (int j = 0; j <= longs; j++) {
				double lng = 2 * M_PI * (double)(j - 1) / longs;
				double x = cos(lng);
				double y = sin(lng);

				glNormal3f(x * zr0, y * zr0+r, z0);
				glVertex3f(x * zr0, y * zr0+r, z0);
				glNormal3f(x * zr1, y * zr1+r, z1);
				glVertex3f(x * zr1, y * zr1+r, z1);
			}
			glEnd();
		}

	}
};


#endif
