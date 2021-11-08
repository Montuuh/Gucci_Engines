#include "Application.h"
#include "ModuleGui.h"



ModuleGui::ModuleGui(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    demoWindow = false;
    guiPanelConfig = new GuiPanelConfig(App, false);
    guiPanelConsole = new GuiPanelConsole(App, false);
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
    ImGuiContext* ctx = ImGui::CreateContext();
    ImGui::SetCurrentContext(ctx);

    // ImGui IO init
    io = ImGui::GetIO(); 
    (void)io;
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

    // Add gui panels
    AddGuiPanel(guiPanelConfig);
    AddGuiPanel(guiPanelConsole);

    // Setting ImGui style (colors, etc)
    /*style = &ImGui::GetStyle();*/
    /*style->Colors[ImGuiCol_Text] = */
    return ret;
}

update_status ModuleGui::PreUpdate(float dt)
{
    // Create ImGui new frames
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame(App->window->window);
    ImGui::NewFrame();

    // Set some io flags
    io.WantCaptureKeyboard = true;
    io.WantTextInput = true;
    

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleGui::Update(float dt)
{
    update_status ret = update_status::UPDATE_CONTINUE;

    // Manage Input Hotkeys
    ret = InputManagement();
    if (ret == update_status::UPDATE_CONTINUE);
    else return ret;

    // Show help imgui window
    if (demoWindow) ImGui::ShowDemoWindow();

    // Call every update of every gui panel
    std::vector<GuiPanel*>::iterator it = list_panels.begin();
    while (it != list_panels.end())
    {
        if ((*it)->active)
        {
            ret = (*it)->PreUpdate();
            if (ret == update_status::UPDATE_CONTINUE);
            else return ret;
            ret = (*it)->Update();
            if (ret == update_status::UPDATE_CONTINUE);
            else return ret;
            ret = (*it)->PostUpdate();
            if (ret == update_status::UPDATE_CONTINUE);
            else return ret;
        }
        it++;
    }

    // Main Menu Bar
    ret = MainMenu();
    if (ret == update_status::UPDATE_CONTINUE);
    else return ret;

	return ret;
}

update_status ModuleGui::PostUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

void ModuleGui::RenderGui()
{
    ImGui::EndFrame();

    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
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
            if (ImGui::MenuItem("Quit", "ESC")) // TODO: No sé como poner el ESC que sale en el engine.exe del handout02
            {
                ImGui::EndMenu();
                return UPDATE_STOP;
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Console", "1")); // Toggle console panel active bool
            if (ImGui::MenuItem("Configuration", "4")) // Toggle configuration panel active bool
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

update_status ModuleGui::InputManagement()
{
    update_status ret = update_status::UPDATE_CONTINUE;

    ////// Console and cofiguration window hotkeys
     if (App->input->keyboard[SDL_SCANCODE_1] == KEY_DOWN)
         guiPanelConsole->active = !guiPanelConsole->active;
    if (App->input->keyboard[SDL_SCANCODE_4] == KEY_DOWN)
        guiPanelConfig->active = !guiPanelConfig->active;

    ////// Quit hotkey
    if (App->input->keyboard[SDL_SCANCODE_ESCAPE] == KEY_UP)
        return update_status::UPDATE_STOP;

    return ret;
}

void ModuleGui::AddGuiPanel(GuiPanel* guiPanel)
{
    list_panels.push_back(guiPanel);
}