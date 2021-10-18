#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleGui.h"


class Application
{
public:
	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	void RequestBrowser(LPCSTR lpFile);

	const char* GetAppName();
	void SetAppName(std::string _appName);
	const char* GetOrgName();
	void SetOrgName(std::string _orgName);
	const int GetMaxFps();
	void SetMaxFps(int _maxFps);
	const int GetFps();
	

private:
	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();

public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleGui* gui;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;

private:
	Timer	ms_timer;
	float	dt;

	std::vector<Module*> list_modules;

	std::string appName;
	std::string orgName;

	int maxFps;
};

#endif