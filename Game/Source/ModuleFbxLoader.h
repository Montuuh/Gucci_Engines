#ifndef __MODULE_FBX_LOADER_H__
#define __MODULE_FBX_LOADER_H__

#include "Module.h"
#include "assimp/include/assimp/vector3.h"
#include "assimp/include/assimp/cimport.h"
#include "assimp/include/assimp/scene.h"
#include "assimp/include/assimp/postprocess.h"

#pragma comment (lib, "assimp.lib")


class ModuleFbxLoader : public Module
{
public:
	ModuleFbxLoader(Application* app, bool start_enabled = true);
	~ModuleFbxLoader();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void LoadFbx(const char* path,const char* tex);

	GLuint vertexToGL(aiVector3D* vertices, size_t numVertices);
	GLuint indicesToGL(aiFace* faces, size_t numFaces);
	GLuint normalsToGL(aiVector3D* normals, size_t numNormals);
	GLuint textCoordToGL(aiVector3D* coord, size_t numTextCoor);
	GLuint textureToGL(const char* path);

	bool Render();



	std::vector<aiMesh*> fbxList;



private:

};

#endif