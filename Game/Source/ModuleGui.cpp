#include "Globals.h"
#include "Application.h"
#include "ModuleGui.h"

#include "GuiPanel.h"
#include "GuiPanelConfig.h"

#include "imgui\include\imgui.h"
#include "imgui\include\imgui_impl_opengl2.h"
#include "imgui\include\imgui_impl_sdl.h"

#include "MathGeoLib/include/MathGeoLib.h"

ModuleGui::ModuleGui(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleGui::~ModuleGui()
{
    for (int i = 0; i <= list_panels.size() - 1; i++)
    {
        delete list_panels[i];
    }
}

// Called before render is available
bool ModuleGui::Init()
{
    bool ret = true;

    LOG("Starting Module UI");

    // Application init: create a dear imgui context, setup some options, load fonts...
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // ImGui Init & Backends Init
    ImGui_ImplOpenGL2_Init();
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);

    // Style Initialization
    ImGui::StyleColorsClassic;

	return ret;
}

bool ModuleGui::Start()
{
    bool ret = true;

    demoWindow = false;

    guiPanelConfig = new GuiPanelConfig(App, false);
    AddGuiPanel(guiPanelConfig);

    return ret;
}

update_status ModuleGui::PreUpdate(float dt)
{
    // Create ImGui new frames
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame(App->window->window);
    ImGui::NewFrame();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleGui::Update(float dt)
{
    update_status ret = update_status::UPDATE_CONTINUE;

    // Show help imgui window
    if (demoWindow) ImGui::ShowDemoWindow();

    // Call every update of every gui panel
    std::vector<GuiPanel*>::iterator it = list_panels.begin();
    while (it != list_panels.end())
    {
        if ((*it)->active)
        {
            ret = (*it)->PreUpdate();
            if (ret != update_status::UPDATE_CONTINUE) return update_status::UPDATE_ERROR;
            ret = (*it)->Update();
            if (ret != update_status::UPDATE_CONTINUE) return update_status::UPDATE_ERROR;
            ret = (*it)->PostUpdate();
            if (ret != update_status::UPDATE_CONTINUE) return update_status::UPDATE_ERROR;
        }
        it++;
    }

    // Main Menu Bar
    ret = MainMenu();

	return ret;
}

update_status ModuleGui::PostUpdate(float dt)
{
    ImGui::EndFrame();

    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

bool ModuleGui::CleanUp()
{
    LOG("Destroying Module UI");

    // ImGui CleanUp
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return true;
}

update_status ModuleGui::MainMenu()
{
    update_status ret = update_status::UPDATE_CONTINUE;

    ImGui::BeginMainMenuBar();
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Quit")) // TODO: No s� como poner el ESC que sale en el engine.exe del handout02
            {
                ImGui::EndMenu();
                return UPDATE_STOP;
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Console")); // Toggle console panel active bool
            if (ImGui::MenuItem("Configuration")) // Toggle configuration panel active bool
            {
                guiPanelConfig->active = !guiPanelConfig->active;
            }
            
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("Gui Demo")) demoWindow = !demoWindow;
            if (ImGui::MenuItem("Documentation")) App->RequestBrowser("https://github.com/Montuuh/Gucci_Engines");
            if (ImGui::MenuItem("Download Latest")) App->RequestBrowser("https://github.com/Montuuh/Gucci_Engines/releases");
            if (ImGui::MenuItem("Report a bug")) App->RequestBrowser("https://github.com/Montuuh/Gucci_Engines/issues");
            if (ImGui::MenuItem("About"));

            ImGui::EndMenu();
        }

    }
    ImGui::EndMainMenuBar();

    return ret;
}

void ModuleGui::AddGuiPanel(GuiPanel* guiPanel)
{
    list_panels.push_back(guiPanel);
}