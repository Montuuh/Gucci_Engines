#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#define GLEW_STATIC


ModuleWindow::ModuleWindow(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	window = NULL;
	screen_surface = NULL;
	screenWidth = SCREEN_WIDTH;
	screenHeight = SCREEN_HEIGHT;
	fullscreen = false;
	resizable = true;
	borderless = false;
	fullscreenDesktop = false;

	active = true;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	GLenum err = glewInit();
	////? check for errors
	LOG("Using Glew %s", glewGetString(GLEW_VERSION));
	// Should be 2.0

	LOG("Vendor: %s", glGetString(GL_VENDOR));
	LOG("Renderer: %s", glGetString(GL_RENDERER));
	LOG("OpenGL version supported %s", glGetString(GL_VERSION));
	LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));


	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		// Setting window parameters
		screenWidth = SCREEN_WIDTH * SCREEN_SIZE;
		screenHeight = SCREEN_HEIGHT * SCREEN_SIZE;

		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
		if (fullscreen == true)
			flags |= SDL_WINDOW_FULLSCREEN;
		if (resizable == true)
			flags |= SDL_WINDOW_RESIZABLE;
		if (borderless == true)
			flags |= SDL_WINDOW_BORDERLESS;
		if (fullscreenDesktop == true)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		
		// Creating window
		window = SDL_CreateWindow(App->GetAppName(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, flags);
		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
			SetBrightness(SDL_GetWindowBrightness(window));
		}
	}

	return ret;
}

update_status ModuleWindow::PreUpdate(float dt)
{
	update_status ret = update_status::UPDATE_CONTINUE;


	return ret;
}

update_status ModuleWindow::PostUpdate(float dt)
{
	update_status ret = update_status::UPDATE_CONTINUE;

	if (!active) return update_status::UPDATE_STOP;

	return ret;
}



// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}
