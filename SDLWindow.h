#ifndef SDLWindow_Header
#define SDLWindow_Header

#include <SDL2/SDL.h>
#include "cairo.h"
#include "cairosdl.h"

class SDLWindow {
public:
	SDLWindow();
	
	cairo_t* getCairo();
	
protected:
	SDL_Window* m_window;
};

#endif