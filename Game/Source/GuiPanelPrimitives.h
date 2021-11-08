#ifndef __GUI_PANEL_PRIMITIVES_H__
#define __GUI_PANEL_PRIMITIVES_H__

#include "GuiPanel.h"

class GuiPanelPrimitives : public GuiPanel
{
public:

	GuiPanelPrimitives(Application* App, bool start_enabled = false);
	~GuiPanelPrimitives();

	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
private:

public:

private:
	// This bool servers for Begin(), as a parameter to determine if the console window is open or not
	bool buttonActive;
};

#endif

