#include "Globals.h"
#include "Application.h"
#include "GuiPanelConfig.h"
#include "ModuleWindow.h"

#include "imgui\include\imgui.h"

GuiPanelConfig::GuiPanelConfig(Application* App, bool start_enabled) : GuiPanel(App, start_enabled), fpsLog(100), msLog(100)
{
	name = "panel config";
	active = true;
    
    buttonActive = true;
    windowActive = App->window->active;

    fpsCounter = 0;
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
    UpdateFpsLog();

    ImGui::Begin("Configuration", &buttonActive); // Configuration window

    // Manage close button on configuration window
    if (!buttonActive)
    {
        buttonActive = !buttonActive;
        active = !active;
    }

    // 1st Config Menu: Options
    if (ImGui::BeginMenu("Options")) 
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

    // 2nd Config Menu (With title): Application
    if (ImGui::CollapsingHeader("Application")) 
    {
        /////// App Name input text
        static char appName[50] = "";
        strcpy_s(appName, 50, App->GetAppName());
        if (ImGui::InputText("App Name", appName, IM_ARRAYSIZE(appName)))
        {
            App->SetAppName(appName);
        }

        /////// Organization Name input text
        char orgName[200];
        strcpy_s(orgName, 200, App->GetOrgName());
        if (ImGui::InputText("Organization", orgName, IM_ARRAYSIZE(orgName)))
        {
            App->SetOrgName(orgName);
        }
        
        /////// Max Fps Slider
        maxFps = App->GetMaxFps();
        if (ImGui::SliderInt("Max FPS", &maxFps, 1, 120))
        {
            App->SetMaxFps(maxFps);
        }

        /////// Limit framerate counter
        ImGui::Text("Limit Framerate:");
        ImGui::SameLine();
        std::string temp = std::to_string(App->GetMaxFps()); // int to const char* converter
        const char* temp2 = temp.c_str();
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));
        ImGui::Text(temp2);
        ImGui::PopStyleColor();

        /////// Average 100 framerate counter
        ImGui::Text("Average Framerate:");
        ImGui::SameLine();
        temp = std::to_string(average100Fps); // int to const char* converter
        temp2 = temp.c_str();
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));
        ImGui::Text(temp2);
        ImGui::PopStyleColor();

        /////// FPS Graph
        std::string tempTitle = "Framerate ";
        tempTitle += std::to_string((int)App->GetFps());
        ImGui::PlotHistogram("##framerate", &fpsLog[0], fpsLog.size(), 0, tempTitle.c_str(), 0.0f, 100.0f, ImVec2(310.0f, 100.0f));

        /////// Milliseconds Graph
        tempTitle = "Milliseconds ";
        tempTitle += std::to_string((int)App->GetMs());
        ImGui::PlotHistogram("##milliseconds", &msLog[0], msLog.size(), 0, tempTitle.c_str(), 0.0f, 100.0f, ImVec2(310.0f, 100.0f));
    }

    // 3rd Config Menu (With title): Window
    if (ImGui::CollapsingHeader("Window")) 
    {
        /////// Active window checkbox
        if (ImGui::Checkbox("Active", &windowActive))
        {
            App->window->active = !App->window->active;
        }

        /////// App Icon input
        

        /////// Brigthness slider
        float brightness = App->window->GetBrightness();
        if (ImGui::SliderFloat("Brightness", &brightness, 0.000f, 1.000f))
        {
             App->window->SetBrightness(brightness);
        }

        /////// Width slider
        int width = App->window->GetWidth();
        if (ImGui::SliderInt("Width", &width, 640, App->window->GetMaxWidth()) && !(App->window->IsFullscreen() || App->window->IsFullscreenDesktop()) && App->window->IsResizable())
        {
            App->window->SetWidth(width);
        }

        /////// Height slider
        int height = App->window->GetHeight();
        if (ImGui::SliderInt("Height", &height, 480, App->window->GetMaxHeight()) && !(App->window->IsFullscreen() || App->window->IsFullscreenDesktop()) && App->window->IsResizable())
        {
            App->window->SetHeight(height);
        }

        /////// Refresh rate
        ImGui::Text("Refresh Rate:");
        ImGui::SameLine();
        std::string temp = std::to_string(App->window->GetRefreshRate()); // int to const char* converter
        const char* temp2 = temp.c_str();
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));
        ImGui::Text(temp2);
        ImGui::PopStyleColor();

        /////// Fullscreen checkbox
        bool fullscreen = App->window->IsFullscreen();
        if (ImGui::Checkbox("Fullscreen", &fullscreen))
        {
            App->window->SetFullscreen(fullscreen);
        }

        ImGui::SameLine();

        /////// Resizable checkbox
        bool resizable = App->window->IsResizable();
        if (ImGui::Checkbox("Resizable", &resizable))
        {
            App->window->SetResizable(resizable);
        }

        /////// Borderless checkbox
        bool borderless = App->window->IsBorderless();
        if (ImGui::Checkbox("Borderless", &borderless))
        {
            App->window->SetBorderless(borderless);
        }

        ImGui::SameLine();

        /////// Fullscreen Desktop checkbox
        bool fullDesktop = App->window->IsFullscreenDesktop();
        if (ImGui::Checkbox("Full Desktop", &fullDesktop))
        {
            App->window->SetFullscreenDesktop(fullDesktop);
        }
    }

    // 3rd Config Menu (With title): File system
    if (ImGui::CollapsingHeader("File System")) 
    {
        /////// Active file system checkbox
        if (ImGui::Checkbox("Active", &fileSystemActive))
        {

        }
    }

    // 4th Config Menu (With title): Input
    if (ImGui::CollapsingHeader("Input"))
    {
        /////// Active input checkbox
        if (ImGui::Checkbox("Active", &inputActive))
        {

        }
    }

    // 5th Config Menu (With title): Hardware
    if (ImGui::CollapsingHeader("Hardware"))
    {
        /////// Active hardware checkbox
        if (ImGui::Checkbox("Active", &hardwareActive))
        {

        }
    }
    ImGui::End(); // End configuration window

    return update_status::UPDATE_CONTINUE;
}

update_status GuiPanelConfig::PostUpdate()
{

    return update_status::UPDATE_CONTINUE;
}

void GuiPanelConfig::UpdateFpsLog()
{
    static int fpsSum = 0;
    if (fpsCounter < 100)
        fpsCounter++;
    else // Move 1 element from right to left of the vector --> fpsLog[0] = fpsLog[1] --> fpsLog[i] = fpsLog[i+1]
    {
        int i = 0;
        while (i < 99)
        {
            fpsLog[i] = fpsLog[i + 1];
            msLog[i] = msLog[i + 1];
            fpsSum += fpsLog[i];
            i++;
        }
    }
    fpsLog[fpsCounter - 1] = App->GetFps(); // To update last element of the array, after having moved it
    msLog[fpsCounter - 1] = App->GetMs();

    if (fpsCounter == 100)
    {
        average100Fps = fpsSum / 100;
        fpsSum = 0;
    }
}