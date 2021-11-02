#include "Application.h"
#include "ModuleScene.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleScene::~ModuleScene()
{}

bool ModuleScene::Init()
{
	bool ret = true;

	return ret;
}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}

update_status ModuleScene::Update(float dt)
{
	update_status ret = update_status::UPDATE_CONTINUE;

	return ret;
}

bool ModuleScene::CleanUp()
{
	LOG("Unloading Intro scene");
	update_status ret = update_status::UPDATE_CONTINUE;

	return ret;
}
