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
    // Application init: create a dear imgui context, setup some options, load fonts
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Application main loop

    // ImGui Inits
    ImGui_ImplOpenGL2_Init();
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);

    ImGui::StyleColorsClassic;

	return true;
}



update_status ModuleUI::PreUpdate(float dt)
{
    // Create ImGui new frames
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // Main Menu Bar
    ImGui::BeginMainMenuBar();
    if (ImGui::MenuItem("Quit")) return UPDATE_STOP;
    ImGui::MenuItem("Holi");
    ImGui::EndMainMenuBar();

	return UPDATE_CONTINUE;
}

update_status ModuleUI::Update(float dt)
{
    // Show help imgui window
    ImGui::ShowDemoWindow();

	return UPDATE_CONTINUE;
}

update_status ModuleUI::PostUpdate(float dt)
{
    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

void ModuleUI::SetTitle(const char* title)
{

}

bool ModuleUI::CleanUp()
{
    LOG("Destroying Imgui interface");

    // ImGui CleanUp
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return true;
}