#include "Globals.h"
#include "Application.h"
#include "GuiManager.h"

#include "imgui\include\imgui.h"
#include "imgui\include\imgui_impl_opengl2.h"
#include "imgui\include\imgui_impl_sdl.h"

#include "MathGeoLib/include/MathGeoLib.h"

GuiManager::GuiManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
GuiManager::~GuiManager()
{
}

// Called before render is available
bool GuiManager::Init()
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

bool GuiManager::Start()
{
    bool ret = true;

    demoWindow = false;

    return ret;
}

update_status GuiManager::PreUpdate(float dt)
{
    // Create ImGui new frames
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame(App->window->window);
    ImGui::NewFrame();

	return update_status::UPDATE_CONTINUE;
}

update_status GuiManager::Update(float dt)
{
    update_status ret = update_status::UPDATE_CONTINUE;

    // Show help imgui window
    if (demoWindow) ImGui::ShowDemoWindow();

    /////////////////////////////////////
    // TESTING

    ImGui::Begin("Configuration");
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

    if (ImGui::CollapsingHeader("Application"))
    {
    }

    if (ImGui::CollapsingHeader("Window"))
    {
        if (ImGui::Checkbox("Active", &boool))
        {
            boool = !boool;
        }
        if (ImGui::Checkbox("Fullscreen", &boool))
        {
            boool = !boool;
        }
        ImGui::SameLine();
        if (ImGui::Checkbox("Resizable", &boool))
        {
            boool = !boool;
        }
        if (ImGui::Checkbox("Borderless", &boool))
        {
            boool = !boool;
        }
        ImGui::SameLine();
        if (ImGui::Checkbox("Full Desktop", &boool))
        {
            boool = !boool;
        }
    }

    if (ImGui::CollapsingHeader("File System"))
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
    ////////////////////////////////////

    ///////////////////////////
    // TODO: 
    // Vale voy a escribir mi idea para mi yo del futuro o para ti chito. Hay que hacer algo tipo llamar a cada preupdate, update y post update de cada gui window. Cómo?
    // Algo parecido a como se llaman a todos los modulos pero con una lista de gui panels en vez de modulos. Añadir un if(list_panels.active == true) then call updates
    // Lo tengo que hacer y testear aún, lo de arriba funciona. Hay que hacer gui windows de:
    // Configuration, Console, About...
    // Lo de arriba que esta entre rallitas es como si fuera GuiConfiguration.h (TODO)
    // Ni Console ni about hecho
    /////////////////////////

    // Main Menu Bar
    ret = MainMenu();

	return ret;
}

update_status GuiManager::PostUpdate(float dt)
{
    ImGui::EndFrame();

    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

bool GuiManager::CleanUp()
{
    LOG("Destroying Module UI");

    // ImGui CleanUp
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return true;
}

update_status GuiManager::MainMenu()
{
    update_status ret = update_status::UPDATE_CONTINUE;

    ImGui::BeginMainMenuBar();
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Quit")) // TODO: No sé como poner el ESC que sale en el engine.exe del handout02
            {
                ImGui::EndMenu();
                return UPDATE_STOP;
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Console")); // Toggle console panel active bool
            if (ImGui::MenuItem("Configuration")); // Toggle configuration panel active bool
            
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