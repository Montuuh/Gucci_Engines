#ifndef __MODULE_FBX_LOADER_H__
#define __MODULE_FBX_LOADER_H__

#include "Module.h"

class ModuleFbxLoader : public Module
{
public:
	ModuleFbxLoader(Application* app, bool start_enabled = true);
	~ModuleFbxLoader();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void LoadFbx();

private:

};

#endif