#include "Globals.h"
#include "Application.h"
#include "GuiPanelConsole.h"

#include "imgui\include\imgui.h"

GuiPanelConsole::GuiPanelConsole(Application* App, bool start_enabled) : GuiPanel(App, start_enabled)
{
    name = "panel console";
    active = false;

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

    // Console window Begin()
    ImGui::Begin("Console", &buttonActive, ImGuiWindowFlags_NoFocusOnAppearing); 

    // Manage close button on console window
    if (!buttonActive)
    {
        buttonActive = true;
        active = false;
    }

    for (int i = 0; i < GetConsoleSize(); i++)
    {
        ImGui::Text(GetConsoleText(i).c_str());
    }

    // Console window End()
    ImGui::End();

    return ret;
}

update_status GuiPanelConsole::PostUpdate()
{

    return update_status::UPDATE_CONTINUE;
}