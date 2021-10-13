#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include "Module.h"
#include "GuiPanel.h"

class Application;

class ModuleUI : public Module
{
public:

	ModuleUI(Application* app, bool start_enabled = true);
	~ModuleUI();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	update_status MainMenu();

public:
	bool demoWindow;
	std::vector<GuiPanel*> list_gui;
	
};

#endif // __Module_H__