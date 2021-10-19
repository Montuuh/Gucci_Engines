#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "glew/include/GL/glew.h"



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



	//GLenum err = glewInit();
	////… check for errors
	//LOG("Using Glew %s", glewGetString(GLEW_VERSION));
	// Should be 2.0

	//LOG("Vendor: %s", glGetString(GL_VENDOR));
	//LOG("Renderer: %s", glGetString(GL_RENDERER));
	//LOG("OpenGL version supported %s", glGetString(GL_VERSION));
	//LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));


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
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		
		// Creating window
		window = SDL_CreateWindow(App->GetAppName(), 0, 30, screenWidth, screenHeight, flags);
		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}


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
