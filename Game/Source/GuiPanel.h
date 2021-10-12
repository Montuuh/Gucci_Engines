#ifndef __GUIPANEL_H__
#define __GUIPANEL_H__

#include "Globals.h"

class Application;

class GuiPanel
{
public:
	Application* App;
	std::string name;
	bool active;

	GuiPanel(Application* parent, bool start_enabled = false) : App(parent), active(start_enabled) {}

	virtual ~GuiPanel() {}

	virtual bool Start() { return true; }

	virtual update_status Update() { return update_status::UPDATE_CONTINUE; }

	virtual bool CleanUp() { return true; }


private:

};


#endif
