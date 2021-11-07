#include "Globals.h"
#include "Application.h"
#include "ModuleFbxLoader.h"



ModuleFbxLoader::ModuleFbxLoader(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleFbxLoader::~ModuleFbxLoader()
{}

bool ModuleFbxLoader::Init()
{
	bool ret = true;



	return ret;
}

update_status ModuleFbxLoader::PreUpdate(float dt)
{
	update_status ret = update_status::UPDATE_CONTINUE;


	return ret;
}

update_status ModuleFbxLoader::Update(float dt)
{
	update_status ret = update_status::UPDATE_CONTINUE;


	return ret;
}

update_status ModuleFbxLoader::PostUpdate(float dt)
{
	update_status ret = update_status::UPDATE_CONTINUE;


	return ret;
}

bool ModuleFbxLoader::CleanUp() 
{ 
	bool ret = true;



	return ret; 
}

void ModuleFbxLoader::LoadFbx()
{

}