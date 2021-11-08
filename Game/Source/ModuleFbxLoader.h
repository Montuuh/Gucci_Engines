#ifndef __MODULE_FBX_LOADER_H__
#define __MODULE_FBX_LOADER_H__

#include "Module.h"
#include "assimp/include/assimp/vector3.h"
#include "assimp/include/assimp/cimport.h"
#include "assimp/include/assimp/scene.h"
#include "assimp/include/assimp/postprocess.h"
#include "Mesh.h"

#pragma comment (lib, "assimp.lib")

class Application;
class aiMesh;
class aiScene;

class ModuleFbxLoader : public Module
{
public:
	ModuleFbxLoader(Application* app, bool start_enabled = true);
	~ModuleFbxLoader();

	bool Init();
	bool Start();
	bool CleanUp();

	// Load a mesh from a path
	void LoadMeshToScene(const char* path);
	
	// Fbx Loader
	std::vector<Mesh*> LoadFbx(const char* path);

	// Mesh loader (vertexs, normals, indices and texture coords)
	Mesh* ModuleFbxLoader::LoadMesh(aiMesh* aiMesh);

	Texture* LoadTextureToScene(const char* path, const char* name);
	Texture* LoadTexture(const aiScene* scene, aiMesh* mesh, const char* path, const char* name);

private:
	
public:
	std::vector<Mesh*> fbxList;
};

#endif