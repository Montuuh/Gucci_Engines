#ifndef __ModuleGUI_H__
#define __ModuleGUI_H__

#include "Module.h"
#include "GuiPanel.h"

class Application;

class GuiManager : public Module
{
public:

	GuiManager(Application* app, bool start_enabled = true);
	~GuiManager();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	update_status MainMenu();

public:
	bool demoWindow;
	std::vector<GuiPanel*> list_panels;

	bool boool = false;
	
};

#endif // __Module_H__