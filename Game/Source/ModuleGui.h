#ifndef __ModuleGUI_H__
#define __ModuleGUI_H__

#include "Module.h"
#include "GuiPanel.h"
#include "GuiPanelConfig.h"

class Application;

class ModuleGui : public Module
{
public:

	ModuleGui(Application* app, bool start_enabled = true);
	~ModuleGui();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	update_status MainMenu();

	update_status InputManagement();

	void AddGuiPanel(GuiPanel* guiPanel);

public:
	bool demoWindow;
	std::vector<GuiPanel*> list_panels;

	GuiPanelConfig* guiPanelConfig;
	
	/*ImGuiStyle* style;*/
};

#endif // __Module_H__