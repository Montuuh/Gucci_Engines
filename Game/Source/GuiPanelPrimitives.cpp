#include "Globals.h"
#include "Application.h"
#include "GuiPanelPrimitives.h"
#include "ModuleRenderer3D.h"

#include "imgui\include\imgui.h"

GuiPanelPrimitives::GuiPanelPrimitives(Application* App, bool start_enabled) : GuiPanel(App, start_enabled)
{
    name = "panel primitives";
    active = false;

    buttonActive = true;
}

GuiPanelPrimitives::~GuiPanelPrimitives()
{

}

update_status GuiPanelPrimitives::PreUpdate()
{

    return update_status::UPDATE_CONTINUE;
}

update_status GuiPanelPrimitives::Update()
{
    update_status ret = update_status::UPDATE_CONTINUE;

    // Set some window configuration before calling Begin()
    ImVec2 minSize = { 150, 250 };
    ImVec2 maxSize = { 200, 300 };
    ImGui::SetNextWindowSize(minSize, ImGuiCond_Once);
    ImGui::SetNextWindowPos({ 0, 25 }, ImGuiCond_Once);
    ImGui::SetNextWindowSizeConstraints(minSize, maxSize);

    // Console window Begin()
    ImGui::Begin("Primitives", &buttonActive, ImGuiWindowFlags_NoFocusOnAppearing);

    // Manage close button on console window
    if (!buttonActive)
    {
        buttonActive = true;
        active = false;
    }

    if (ImGui::Checkbox("Cube", &App->renderer3D->cubePrimitiveDraw));
    if (ImGui::Checkbox("Pyramid", &App->renderer3D->pyramidPrimitiveDraw));
    if (ImGui::Checkbox("Sphere", &App->renderer3D->spherePrimitiveDraw));
    if (ImGui::Checkbox("Cylinder", &App->renderer3D->cylinderPrimitiveDraw));

    // Console window End()
    ImGui::End();

    return ret;
}

update_status GuiPanelPrimitives::PostUpdate()
{

    return update_status::UPDATE_CONTINUE;
}