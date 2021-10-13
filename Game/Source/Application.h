#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "GuiManager.h"


class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	GuiManager* gui;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;

private:

	Timer	ms_timer;
	float	dt;
	std::vector<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	void RequestBrowser(LPCSTR lpFile);

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();

	
};

#endif