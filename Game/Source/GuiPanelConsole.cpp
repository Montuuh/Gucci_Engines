#include "Globals.h"
#include "Application.h"
#include "GuiPanelConsole.h"

#include "imgui\include\imgui.h"

GuiPanelConsole::GuiPanelConsole(Application* App, bool start_enabled) : GuiPanel(App, start_enabled)
{
    name = "panel console";
    active = true;

    buttonActive = true;
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
    update_status ret = update_status::UPDATE_CONTINUE;

    // Set some window configuration before calling Begin()
    ImVec2 minSize = { 500, 300 };
    ImVec2 maxSize = { 700, 450 };
    ImGui::SetNextWindowSize(minSize, ImGuiCond_Once);
    ImGui::SetNextWindowPos({ 0, 25 }, ImGuiCond_Once);
    ImGui::SetNextWindowSizeConstraints(minSize, maxSize);

    // Console window Begin()
    ImGui::Begin("Console", &buttonActive, ImGuiWindowFlags_NoFocusOnAppearing); 

    // Manage close button on configuration window
    if (!buttonActive)
    {
        buttonActive = !buttonActive;
        active = !active;
    }

    // Console window End()
    ImGui::End();

    return ret;
}

update_status GuiPanelConsole::PostUpdate()
{

    return update_status::UPDATE_CONTINUE;
}