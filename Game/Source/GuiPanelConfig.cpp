#include "Globals.h"
#include "Application.h"
#include "GuiPanelConfig.h"

#include "imgui\include\imgui.h"

GuiPanelConfig::GuiPanelConfig(Application* App, bool start_enabled) : GuiPanel(App, start_enabled)
{
	name = "panel config";
	active = true;
}

GuiPanelConfig::~GuiPanelConfig()
{

}

update_status GuiPanelConfig::PreUpdate()
{

    return update_status::UPDATE_CONTINUE;
}

update_status GuiPanelConfig::Update()
{
    bool boool = true;

    ImGui::Begin("Configuration"); // Configuration window
    if (ImGui::BeginMenu("Options")) // 1st Config Menu: Options
    {
        if (ImGui::MenuItem("Set Defaults"))
        {

        }
        if (ImGui::MenuItem("Save"))
        {

        }
        if (ImGui::MenuItem("Load"))
        {

        }

        ImGui::EndMenu();
    }

    if (ImGui::CollapsingHeader("Application")) // 2nd Config Menu (With title): Application
    {
        /*std::string str = "Hola";*/
        //ImGui::InputText(str.c_str(), , str.size());
    }

    if (ImGui::CollapsingHeader("Window")) // 3rd Config Menu (With title): Window
    {
        if (ImGui::Checkbox("Active", &boool))
        {
            boool = !boool;
        }
        if (ImGui::Checkbox("Fullscreen", &boool /* should be like App->window->fullscreen */))
        {
            // bool fullscreen = App->GetFullScreen;
            // fullscreen = !fullscreen;
            // App->window->fullscreen = fullscreen;
            // App->SetFullScreen(fullscreen);
            
            boool = !boool;
        }
        ImGui::SameLine();
        if (ImGui::Checkbox("Resizable", &boool /* should be like App->window->resizable */))
        {
            // resizable = App->GetResizableScreen;
            // resizable = !resizable;
            // App->window->resizable = resizable;
            // App->SetResizableScreen(resizable);

            boool = !boool;
        }
        if (ImGui::Checkbox("Borderless", &boool /* should be like App->window->borderless */))
        {
            // borderless = App->GetBorderlessScreen;
            // borderless = !borderless;
            // App->window->borderless = borderless;
            // App->SetBorderlessScreen(borderless);

            boool = !boool;
        }
        ImGui::SameLine();
        if (ImGui::Checkbox("Full Desktop", &boool /* should be like App->window->fullDesktop */))
        {
            // fullDesktop = App->GetFullDesktopScreen;
            // fullDesktop = !fullDesktop;
            // App->window->fullDesktop = fullDesktop;
            // App->SetFullDesktopScreen(fullDesktop);

            boool = !boool;
        }
    }

    if (ImGui::CollapsingHeader("File System")) // 3rd Config Menu (With title): File system
    {
        if (ImGui::Checkbox("Active", &boool))
        {
            boool = !boool;
        }
    }

    if (ImGui::CollapsingHeader("Input"))
    {
        if (ImGui::Checkbox("Active", &boool))
        {
            boool = !boool;
        }
    }

    if (ImGui::CollapsingHeader("Hardware"))
    {
        if (ImGui::Checkbox("Active", &boool))
        {
            boool = !boool;
        }
    }
    ImGui::End(); // End configuration

    return update_status::UPDATE_CONTINUE;
}

update_status GuiPanelConfig::PostUpdate()
{

    return update_status::UPDATE_CONTINUE;
}