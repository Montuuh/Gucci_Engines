#ifndef __GUIPANEL_H__
#define __GUIPANEL_H__

#include "Globals.h"

class Application;

class GuiPanel
{
public:
	Application* App;

	GuiPanel(Application* parent, bool start_enabled = false) : App(parent), active(start_enabled) {}

	virtual ~GuiPanel() {}

	virtual bool Start() { return true; }

	virtual update_status PreUpdate() { return update_status::UPDATE_CONTINUE; }
	virtual update_status Update() { return update_status::UPDATE_CONTINUE; }
	virtual update_status PostUpdate() { return update_status::UPDATE_CONTINUE; }

	virtual bool CleanUp() { return true; }


public:
	std::string name; // name of the current gui window
	bool active; // Bool that activates or not the gui window
};


#endif
