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

	inline void RequestBrowser(LPCSTR lpFile) { ShellExecuteA(NULL, "open", lpFile, NULL, NULL, SW_SHOWNORMAL); }

	inline const char* GetAppName() { return appName.c_str(); }
	inline void SetAppName(std::string _appName) { if (_appName.size() != 0) { appName = _appName; window->SetTitle(appName.c_str()); } }
	inline const char* GetOrgName() { return orgName.c_str(); }
	inline void SetOrgName(std::string _orgName) { if (_orgName.size() != 0) { orgName = _orgName; } }
	inline const int GetMaxFps() { return maxFps; }
	inline void SetMaxFps(int _maxFps) { maxFps = _maxFps; }
	inline const int GetFps() { return 60; } // ToDo
	

private:
	void PrepareUpdate();
	void FinishUpdate();
	inline void AddModule(Module* mod) { list_modules.push_back(mod); }

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