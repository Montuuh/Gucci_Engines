#include "Globals.h"
#include "Application.h"
#include "ModuleFbxLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h";


#include "devil/include/il.h"
#include "devil/include/ilu.h"
#include "devil/include/ilut.h"

ModuleFbxLoader::ModuleFbxLoader(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleFbxLoader::~ModuleFbxLoader()
{}

bool ModuleFbxLoader::Init()
{
	bool ret = true;

	// Call for devil init
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

	return ret;
}

bool ModuleFbxLoader::Start()
{
	bool ret = true;


	return ret;
}

bool ModuleFbxLoader::CleanUp()
{
	bool ret = true;


	return ret;
}

void ModuleFbxLoader::LoadFbxToScene(const char* path, const char* texPath)
{
	std::vector<Mesh*> meshList = LoadFbx(path, texPath);
	for (int i = 0; i < meshList.size(); i++) 
	{
		if (meshList[i] != nullptr) meshList[i]->InitBuffers();
	}
}

// Fbx Loader
std::vector<Mesh*> ModuleFbxLoader::LoadFbx(const char*path, const char* texPath)
{
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (uint i = 0; i < scene->mNumMeshes; i++)
		{
			Mesh* mesh = LoadMesh(scene->mMeshes[i]);
			if (mesh != nullptr) fbxList.push_back(mesh);
			Texture* Tex = LoadTexture(scene, scene->mMeshes[i], texPath, "BakerHouse");
			mesh->SetTexture(Tex);
		}
		aiReleaseImport(scene);
	}
	else
	{
		//TODO: LOG IF SCENE IS NULLPTR
	}


	return fbxList;
}

// Mesh loader (vertexs, normals, indices and texture coords)
Mesh* ModuleFbxLoader::LoadMesh(aiMesh* aiMesh)
{
	// Vertexs loader
	Mesh* mesh = new Mesh();
	mesh->vertexCount = aiMesh->mNumVertices;
	mesh->vertices = new float[mesh->vertexCount * 3];
	memcpy(mesh->vertices, aiMesh->mVertices, sizeof(float) * mesh->vertexCount * 3);


	if (aiMesh->HasFaces())
	{
		// Indices loader
		mesh->indexCount = aiMesh->mNumFaces * 3;
		mesh->indices = new uint[mesh->indexCount];
		for (uint j = 0; j < aiMesh->mNumFaces; j++)
		{
			if (aiMesh->mFaces[j].mNumIndices != 3)
			{
				//TODO: LOG IF NOT TRIANGLES
			}
			else
			{
				memcpy(&mesh->indices[j * 3], aiMesh->mFaces[j].mIndices, sizeof(uint) * 3);
			}
		}

		 // Normals loader
		mesh->normals = new float[aiMesh->mNumVertices * 3]();
		for (uint i = 0; i < aiMesh->mNumVertices; i += 3)
		{
			if (aiMesh->HasNormals())
			{
				mesh->normals[i] = aiMesh->mNormals[i].x;
				mesh->normals[i + 1] = aiMesh->mNormals[i].y;
				mesh->normals[i + 2] = aiMesh->mNormals[i].z;
			}
		}

		// Texture coords loader
		mesh->textureCoordinates = new float[mesh->vertexCount * 2]();
		if (aiMesh->mTextureCoords[0])
		{
			for (uint i = 0; i < aiMesh->mNumVertices; i++)
			{
				mesh->textureCoordinates[i * 2] = aiMesh->mTextureCoords[0][i].x;
				mesh->textureCoordinates[i * 2 + 1] = aiMesh->mTextureCoords[0][i].y;
			}
		}

		// Save the mesh on the mesh list
		fbxList.push_back(mesh);
		return mesh;
	}
	return nullptr;
}

Texture* ModuleFbxLoader::LoadTextureToScene(const char* path, const char* name)
{
	uint id = 0;
	ilGenImages(1, &id);
	ilBindImage(id);

	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	Texture* texture = new Texture();

	// TODO:: Change to ilLoadL
	if (ilLoadImage(path))
	{
		if (ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
		{
			texture->id = id;
			texture->name = name;
			texture->data = ilGetData();
			texture->width = ilGetInteger(IL_IMAGE_WIDTH);
			texture->height = ilGetInteger(IL_IMAGE_HEIGHT);
			texture->format = texture->formatUnsigned = ilGetInteger(IL_IMAGE_FORMAT);
			texture->path = path;
		}

	}

	return texture;
}

Texture* ModuleFbxLoader::LoadTexture(const aiScene* scene, aiMesh* mesh, const char* path, const char* name)
{
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	aiString texPath;
	aiGetMaterialTexture(material, aiTextureType::aiTextureType_DIFFUSE, mesh->mMaterialIndex, &texPath);

	Texture* texture = new Texture();

	texture = LoadTextureToScene(path, name);
	return texture;
}
