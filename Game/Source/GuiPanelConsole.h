#ifndef __GUI_PANEL_CONSOLE_H__
#define __GUI_PANEL_CONSOLE_H__

#include "GuiPanel.h"

class GuiPanelConsole : public GuiPanel
{
public:

	GuiPanelConsole(Application* App, bool start_enabled = false);
	~GuiPanelConsole();

	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
private:

public:

private:

};

#endif
