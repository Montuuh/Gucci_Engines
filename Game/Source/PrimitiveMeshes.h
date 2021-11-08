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


#endif
