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

};

#endif

