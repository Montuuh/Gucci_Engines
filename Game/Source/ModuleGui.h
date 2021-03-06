#ifndef __ModuleGUI_H__
#define __ModuleGUI_H__

#include "Module.h"
#include "Globals.h"

#include "GuiPanel.h"
#include "GuiPanelConfig.h"
#include "GuiPanelConsole.h"
#include "GuiPanelPrimitives.h"

#include "imgui\include\imgui.h"
#include "imgui\include\imgui_impl_opengl2.h"
#include "imgui\include\imgui_impl_sdl.h"

#include "MathGeoLib/include/MathGeoLib.h"

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
	void RenderGui();
	bool CleanUp();

	update_status MainMenu();

	update_status InputManagement();

	void AddGuiPanel(GuiPanel* guiPanel);

public:
	bool demoWindow;
	std::vector<GuiPanel*> list_panels;



	/*ImGuiStyle* style;*/
	
private:
	GuiPanelConfig* guiPanelConfig;
	GuiPanelConsole* guiPanelConsole;
	GuiPanelPrimitives* guiPanelPrimitives;

	ImGuiIO io;
};

#endif // __Module_H__