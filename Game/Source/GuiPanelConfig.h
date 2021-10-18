#ifndef __GUI_PANEL_CONFIG_H__
#define __GUI_PANEL_CONFIG_H__

#include "GuiPanel.h"

class GuiPanelConfig : public GuiPanel
{
public:

	GuiPanelConfig(Application* App, bool start_enabled = false);
	~GuiPanelConfig();
		
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
private:

public:

private:
	// pending to delete. This is only for testing and creating checkboxes
	bool boolTest;

	// Application variables
	int maxFps;
	std::vector<float> fpsLog;
	std::vector<float> msLog;

	// Window variables
	bool windowActive;
	float brightness;
	int width;
	int height;
	bool fullscreen;
	bool resizable;
	bool borderless;
	bool fullDesktop;
	int refreshRate = 60;

	// File System variables
	bool fileSystemActive;

	// Input variables
	bool inputActive;

	// Hardware variables
	bool hardwareActive;

};

#endif

