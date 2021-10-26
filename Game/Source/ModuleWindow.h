#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__


#include "Module.h"
#include "SDL/include/SDL.h"

#include "glew/include/GL/glew.h"
#include "glew/include/GL/wglew.h"

#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "ModuleCamera3D.h"


class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();
	//update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);

	bool Init();
	bool CleanUp();

	inline void SetTitle(const char* title) { SDL_SetWindowTitle(window, title); }

	inline const float GetBrightness() { return SDL_GetWindowBrightness(window); }
	inline void SetBrightness(float brightness) { SDL_SetWindowBrightness(window, brightness); }
	inline const int GetWidth() { return screenWidth; }
	inline const int GetMaxWidth() { SDL_DisplayMode dm; SDL_GetDesktopDisplayMode(0, &dm); return dm.w; }
	inline void SetWidth(int width) { screenWidth = width; SDL_SetWindowSize(window, screenWidth, screenHeight); }
	inline const int GetHeight() { return screenHeight; }
	inline const int GetMaxHeight() { SDL_DisplayMode dm; SDL_GetDesktopDisplayMode(0, &dm); return dm.h; }
	inline void SetHeight(int height) { screenHeight = height; SDL_SetWindowSize(window, screenWidth, screenHeight);  }
	inline const float GetRefreshRate() { SDL_DisplayMode dm; SDL_GetDesktopDisplayMode(0, &dm); return dm.refresh_rate; }
	inline const bool IsFullscreen() { return fullscreen; }
	inline void SetFullscreen(bool _fullscreen) { fullscreen = _fullscreen; if (fullscreen) { fullscreenDesktop = false; SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN); } else { SDL_SetWindowFullscreen(window, 0); } }
	inline const bool IsResizable() { return resizable; }
	inline void SetResizable(bool _resizable) { /*if (!fullscreen && !fullscreenDesktop)*/ { resizable = _resizable; SDL_SetWindowResizable(window, (SDL_bool)resizable); } }
	inline const bool IsBorderless() { return borderless; }
	inline void SetBorderless(bool _borderless) { if (!fullscreen && !fullscreenDesktop) {  borderless = _borderless; SDL_SetWindowBordered(window, (SDL_bool)!borderless); } }
	inline const bool IsFullscreenDesktop() { return fullscreenDesktop; }
	inline void SetFullscreenDesktop(bool _fullscreenDesktop) { fullscreenDesktop = _fullscreenDesktop; if (fullscreenDesktop) { fullscreen = false; SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP); } else { SDL_SetWindowFullscreen(window, 0);  } }

public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screen_surface;

	bool active;

private:
	int screenWidth;
	int screenHeight;
	bool fullscreen;
	bool resizable;
	bool borderless;
	bool fullscreenDesktop;
};

#endif // __ModuleWindow_H__