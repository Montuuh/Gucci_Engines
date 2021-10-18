#include "Globals.h"
#include "Application.h"
#include "GuiPanelConsole.h"

#include "imgui\include\imgui.h"

GuiPanelConsole::GuiPanelConsole(Application* App, bool start_enabled) : GuiPanel(App, start_enabled)
{
    name = "panel console";
    active = true;
}

GuiPanelConsole::~GuiPanelConsole()
{

}

update_status GuiPanelConsole::PreUpdate()
{

    return update_status::UPDATE_CONTINUE;
}

update_status GuiPanelConsole::Update()
{

    return update_status::UPDATE_CONTINUE;
}

update_status GuiPanelConsole::PostUpdate()
{

    return update_status::UPDATE_CONTINUE;
}