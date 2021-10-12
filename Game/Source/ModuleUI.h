
#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include "Module.h"

class Application;

class ModuleUI : public Module
{
public:

	ModuleUI(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleUI();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void SetTitle(const char* title);

public:
};

#endif // __Module_H__