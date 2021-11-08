#include "Globals.h"
#include "Application.h"
#include "ModuleFbxLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h";

ModuleFbxLoader::ModuleFbxLoader(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleFbxLoader::~ModuleFbxLoader()
{}

bool ModuleFbxLoader::Start()
{
	bool ret = true;

	glEnable(GL_DEPTH_TEST);
	GLfloat vertex[] = {
						1,1,1,    -1,1,1,    -1,-1,1,    1,-1,1,        // v0-v1-v2-v3
						1,1,1,     1,-1,1,    1,-1,-1,   1,1,-1,        // v0-v3-v4-v5
						1,1,1,     1,1,-1,   -1,1,-1,   -1,1,1,         // v0-v5-v6-v1
					   -1,1,1,    -1,1,-1,   -1,-1,-1,  -1,-1,1,		// v1-v6-v7-v2
					   -1,-1,-1,   1,-1,-1,   1,-1,1,   -1,-1,1,        // v7-v4-v3-v2
						1,-1,-1,  -1,-1,-1,  -1,1,-1,    1,1,-1  // v4-v7-v6-v5
	};	   
	
	glGenBuffers(1, &m_vertexBuffer); //Generate a buffer for the vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); //Bind the vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 24 * 3, &vertex[0], GL_STATIC_DRAW); //Send the data to OpenGL

	//LoadFbx("Assets/Meshes/BakerHouse.fbx","Assets/Textures/Baker_house.png");

	return ret;
}

void ModuleFbxLoader::LoadFbx(const char*path, const char* tex)
{
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene == nullptr || !scene->HasMeshes())
	{


	}
	else
	{
		for (int i = 0; i < scene->mNumMeshes; i++) //LOAD EVERY MESH TO OPENGL and get the IDs 
		{
			aiMesh* m = scene->mMeshes[i];

			vertexToGL(m->mVertices, m->mNumVertices);
			indicesToGL(m->mFaces, m->mNumFaces);
			normalsToGL(m->mNormals, m->mNumVertices);
			textCoordToGL(m->mTextureCoords[0], m->mNumVertices);//only [0] is used per mesh

			m->mNumFaces * 3;//every face 3 points
			fbxList.push_back(m);
		}
	}

	/*pathaux->data = path;*/
	/*pathaux->Append(path);*/
	//scene->mMaterials[0]->GetTexture(aiTextureType_DIFFUSE, 0, pathaux);
	textureToGL(tex);

	aiReleaseImport(scene);
}

GLuint ModuleFbxLoader::vertexToGL(aiVector3D* vertices, size_t numVertices)
{
	const GLint numberOfCoordPerVertex = 3;
	const size_t  vertexArraySizeinBytes = numVertices * numberOfCoordPerVertex * sizeof(float);

	GLuint verticesID = 0;
	glGenBuffers(1, &verticesID);
	glBindBuffer(GL_ARRAY_BUFFER, verticesID);
	glBufferData(GL_ARRAY_BUFFER, vertexArraySizeinBytes, vertices, GL_STATIC_DRAW);
	glPopMatrix();

	return verticesID;
}

GLuint  ModuleFbxLoader::indicesToGL(aiFace* faces, size_t numFaces)
{
	const GLint   numberIndexPerFace = 3; //triangles
	const GLsizei numberOfIndex = (GLsizei)(numFaces * numberIndexPerFace);
	const size_t  indexArraySizeinBytes = numberOfIndex * sizeof(int);
	unsigned int* indicesArray = (unsigned int*)malloc(indexArraySizeinBytes);
	for (int i = 0; i < numFaces; i++)
	{
		aiFace* f = faces + i;
		*(indicesArray + 0 + i * 3) = f->mIndices[0];
		*(indicesArray + 1 + i * 3) = f->mIndices[1];
		*(indicesArray + 2 + i * 3) = f->mIndices[2];
	};
	GLuint indicesID;
	glGenBuffers(1, &indicesID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexArraySizeinBytes, indicesArray, GL_STATIC_DRAW);

	free(indicesArray); //One loaded to OpenGL, no needed more

	return indicesID;
}

GLuint  ModuleFbxLoader::normalsToGL(aiVector3D* normals, size_t numNormals)
{
	const GLint numberOfCoordPerVertex = 3;
	const size_t  vertexArraySizeinBytes = numNormals * numberOfCoordPerVertex * sizeof(float);

	GLuint normalsID;
	glGenBuffers(1, &normalsID);
	glBindBuffer(GL_ARRAY_BUFFER, normalsID);
	glBufferData(GL_ARRAY_BUFFER, vertexArraySizeinBytes, normals, GL_STATIC_DRAW);

	return normalsID;
}

GLuint ModuleFbxLoader::textCoordToGL(aiVector3D* coord, size_t numTextCoor)
{
	const GLint     numberOfComponents = 2; //2d u,v
	const size_t    textCoordArraySizeinBytes = numTextCoor * sizeof(float) * numberOfComponents;

	// because the librery uses aiVector3D, and we need only u,v
	float* textCoordArray = (float*)malloc(textCoordArraySizeinBytes);
	for (int i = 0; i < numTextCoor; i++)
	{
		*(textCoordArray + i * 2) = coord[i].x;
		*(textCoordArray + i * 2 + 1) = 1.0 - coord[i].y; //this coord image is inverted in the library
														  //nothing to do with coord[i].z, only uv needed
	}

	GLuint textCoordID;
	glGenBuffers(1, &textCoordID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textCoordID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, textCoordArraySizeinBytes, textCoordArray, GL_STATIC_DRAW);

	free(textCoordArray); //DONT NEEDED MORE

	return textCoordID;
}

GLuint  ModuleFbxLoader::textureToGL(const char* path) //<-image texture path
{
	GLuint textureID;
	int height;
	int width;
	int compPerPixel;
	unsigned char* pixels = stbi_load(path, &width, &height, &compPerPixel, STBI_rgb);
	GLint internalFormat = GL_RGBA;
	if (compPerPixel == 3) internalFormat = GL_RGB;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, pixels);

	stbi_image_free(pixels);//DONT NEEDED MORE

	return textureID;

}

void ModuleFbxLoader::Render()
{

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawArrays(GL_QUADS, 0, 24);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);


	for (int i = 0; i < fbxList.size(); i++)
	{
		//vertex
		/*glBindBuffer(GL_ARRAY_BUFFER, fbxList[i]->mNumVertices);
		glVertexPointer(3, GL_FLOAT, 0, NULL);*/
		////normals
		//glBindBuffer(GL_ARRAY_BUFFER, fbxList[i]->mNumVertices);  //help
		//glNormalPointer(GL_FLOAT, 0, NULL);
		////coord
		//glBindBuffer(GL_ARRAY_BUFFER, textCoordIDs_OfMesh_i);
		//glTexCoordPointer(2, GL_FLOAT, 0, NULL);
		////texture
		//glBindTexture(GL_TEXTURE_2D, 0);
		//glBindTexture(GL_TEXTURE_2D, textureID);//only one texture for all scene

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesIDs_OfMesh_i);
		//glDrawElements(GL_TRIANGLES, NumberofIndices_OfMesh_i, GL_UNSIGNED_INT, NULL);

	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

std::vector<aiMesh*> ModuleFbxLoader::GetFbxList()
{
	return fbxList;
}
