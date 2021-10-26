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

	// Set initial app and organization names
	appName = "Gucci Engines";
	orgName = "UPC Citm";

	// Set initial max FPS
	maxFps = 60;

	frameStart = 0;
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
	
	lastFrameMsTimer.Start();
	ms_timer.Start();

	return ret;
}

// Call this function before going through PreUpdate, Update and PostUpdate on each module
void Application::PrepareUpdate()
{
	lastFrameMsTimer.Start();
	frameStart = ms_timer.Read();

	// Start frame timing
	totalFrames++;
	startTicks = SDL_GetTicks();
	startPerf = SDL_GetPerformanceCounter();

}

// Call this function after having gone through PreUpdate, Update and PostUpdate on each module
void Application::FinishUpdate()
{
	int frameEnd = ms_timer.Read();

	// Cap FPS
	if ((1000.0f / (float)maxFps) > dt)
	{
		SDL_Delay((1000.0f / (float)maxFps) - dt);
		dt = (1000.0f / (float)maxFps);
	}

	// End frame timing
	Uint32 endTicks = SDL_GetTicks();
	Uint64 endPerf = SDL_GetPerformanceCounter();
	float frameTime = (endTicks - startTicks) / 1000.0f;
	totalFrameTicks += endTicks - startTicks;

	// Set fps variables
	currentFps = 1.0f / frameTime;
	averageFps = 1000.0f / ((float)totalFrameTicks / totalFrames);

	// Get to know how much took to go from one frame to another
	int msdt = frameEnd - frameStart;
	dt = (float)msdt / 1000.0f;

	// Get to know milliseconds latency
	lastFrameMs = lastFrameMsTimer.Read();
	lastFrameMsTimer.Start();
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