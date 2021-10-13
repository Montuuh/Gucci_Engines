#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"

#include "imgui\include\imgui.h"
#include "imgui\include\imgui_impl_opengl2.h"
#include "imgui\include\imgui_impl_sdl.h"

#include "MathGeoLib/include/MathGeoLib.h"

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleUI::~ModuleUI()
{
}

// Called before render is available
bool ModuleUI::Init()
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

bool ModuleUI::Start()
{
    bool ret = true;

    demoWindow = false;

    return ret;
}

update_status ModuleUI::PreUpdate(float dt)
{
    // Create ImGui new frames
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame(App->window->window);
    ImGui::NewFrame();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleUI::Update(float dt)
{
    update_status ret = update_status::UPDATE_CONTINUE;

    // Show help imgui window
    if (demoWindow) ImGui::ShowDemoWindow();

    // Main Menu Bar
    ret = MainMenu();

	return ret;
}

update_status ModuleUI::PostUpdate(float dt)
{
    ImGui::EndFrame();

    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
    LOG("Destroying Module UI");

    // ImGui CleanUp
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return true;
}

update_status ModuleUI::MainMenu()
{
    update_status ret = update_status::UPDATE_CONTINUE;

    ImGui::BeginMainMenuBar();
    {
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("Gui Demo")) demoWindow = !demoWindow;
            if (ImGui::MenuItem("Documentation")) App->RequestBrowser("https://github.com/Montuuh/Gucci_Engines");
            if (ImGui::MenuItem("Download Latest")) App->RequestBrowser("https://github.com/Montuuh/Gucci_Engines/releases");
            if (ImGui::MenuItem("Report a bug")) App->RequestBrowser("https://github.com/Montuuh/Gucci_Engines/issues");
            if (ImGui::MenuItem("About"));

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Configuration"))
        {

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Quit"))
        {
            ImGui::EndMenu();
            return UPDATE_STOP;
        }
    }
    ImGui::EndMainMenuBar();

    return ret;
}