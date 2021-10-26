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
	void UpdateFpsLog();
public:

private:
	// pending to delete. This is only for testing and creating checkboxes
	bool buttonActive;

	// Application variables
	int maxFps;
	std::vector<float> fpsLog;
	std::vector<float> msLog;
	int fpsCounter;
	int msCounter;
	int average100Fps;

	// Window variables
	bool windowActive;

	// File System variables
	bool fileSystemActive;

	// Input variables
	bool inputActive;

	// Hardware variables
	bool hardwareActive;

};

#endif

