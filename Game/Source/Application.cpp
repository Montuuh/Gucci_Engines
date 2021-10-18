#include "Application.h"
#include "Globals.h"

Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	gui = new ModuleGui(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(gui);
	
	// Scenes

	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application()
{
	for (int i = 0; i <= list_modules.size() - 1; i++) 
	{
		delete list_modules[i];
	}
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	std::vector<Module*>::iterator item = list_modules.begin();

	while(item != list_modules.end() && ret == true)
	{
		ret = (*item)->Init();
		item++;
	}

	// Call Start() in all modules
	LOG("Application Start --------------");
	item = list_modules.begin();

	while(item != list_modules.end() && ret == true)
	{
		ret = (*item)->Start();
		item++;
	}
	
	ms_timer.Start();

	// Set initial app and organization names
	appName = "Gucci Engines";
	orgName = "UPC Citm";

	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	std::vector<Module*>::iterator item = list_modules.begin();

	// Calling all PreUpdates
	while(item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*item)->PreUpdate(dt);
		item++;
	}

	// Calling all updates
	item = list_modules.begin();
	while(item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*item)->Update(dt);
		item++;
	}

	// Calling all PostUpdates
	item = list_modules.begin();
	while(item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*item)->PostUpdate(dt);
		item++;
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = 0; i <= list_modules.size() - 1; i++)
	{
		ret = list_modules[i]->CleanUp();
	}

	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}

void Application::RequestBrowser(LPCSTR lpFile)
{
	ShellExecuteA(NULL, "open", lpFile, NULL, NULL, SW_SHOWNORMAL);
}

// Application Name getter and setter
const char* Application::GetAppName()
{
	return appName.c_str();
}
void Application::SetAppName(std::string _appName)
{
	if (_appName.size() != 0)
	{
		appName = _appName;
		window->SetTitle(appName.c_str());
	}
}

// Organization Name getter and setter
const char* Application::GetOrgName()
{
	return orgName.c_str();
}
void Application::SetOrgName(std::string _orgName)
{
	if (_orgName.size() != 0)
	{
		appName = _orgName;
	}
}

// Max FPS getter and setter
int Application::GetMaxFps()
{
	return 1;
}
void Application::SetMaxFps(int _maxFps)
{

}