#ifndef __MESH_H__
#define __MESH_H__

#include "Globals.h"
#include "glmath.h"
#include "glew/include/GL/glew.h"
#include <gl/GLU.h>
#include <gl/GL.h>


typedef unsigned char GLubyte;
struct Texture
{
	std::string name = "defaultTexture";
	std::string path = "Assets/Textures/";
	uint id = -1;
	int format = -1;
	uint formatUnsigned = -1;
	GLubyte* data = nullptr;
	int width = -1;
	int height = -1;

	~Texture()
	{
		name.clear();
		path.clear();
		data = nullptr;
	}
};

class Mesh
{
public:
	// Mesh constructor (initialized important variables)
	Mesh();
	// Destroy memory created from the buffers of vertexs, indices and normals
	virtual	~Mesh();

	// Initialize all render buffers
	void InitBuffers();

	// Render method to be called that contains every drawing
	virtual void Render() const;
	// Set client states and open Gl render inits
	void InitRender() const;
	// Draw vertex buffer
	void DrawVertices() const;
	// Draw normals buffer
	void DrawNormals() const;
	// Draw texture coords buffer
	void DrawTexture() const;
	// Bind indices
	void BindIndices() const;
	void ApplyTransform() const;
	void DrawElements() const;
	// Disable states and remove buffers
	void EndRender() const;

	// virtual void InnerRender() const;
	/*void DrawVertexNormals() const;
	void DrawFaceNormals() const;*/

	void SetTexture(Texture* texture);

private:

public:
	// Index variables
	unsigned int indexBuffer = 0;
	int indexCount = -1;
	unsigned int* indices = nullptr;

	// Vertex variables
	unsigned int vertexBuffer = 0;
	int vertexCount = -1;
	float* vertices = nullptr;

	// Normals variables
	unsigned int normalsBuffer = 0;
	float* normals = nullptr;

	// Texture Coords variables
	unsigned int textureID = -1;
	unsigned int textureBuffer = 0;
	float* textureCoordinates = nullptr;
	Texture* texture = nullptr;

	mat4x4 transform;
	bool wire;
	bool drawFaceNormals = true;
	bool drawVertexNormals = true;
};

#endif