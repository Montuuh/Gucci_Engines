#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"

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


    ImGui_ImplOpenGL2_Init();
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);

    ImGui::StyleColorsClassic;

	return true;
}



update_status ModuleUI::PreUpdate(float dt)
{
    //ImGui_ImplOpenGL2_NewFrame();
    //ImGui_ImplSDL2_NewFrame();
    //ImGui::NewFrame();
    //ImGui::EndFrame();

	return UPDATE_CONTINUE;
}

update_status ModuleUI::Update(float dt)
{

	return UPDATE_CONTINUE;
}

update_status ModuleUI::PostUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

void ModuleUI::SetTitle(const char* title)
{

}

bool ModuleUI::CleanUp()
{
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    /*ImGui::End();*/
    return true;
}