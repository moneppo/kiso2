#include "SDLWindow.h"

SDLWindow::SDLWindow()
{

   SDL_Init(SDL_INIT_VIDEO); // init video

   // create the window like normal
   m_window = SDL_CreateWindow("Kiso", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
}
	
cairo_t* SDLWindow::getCairo()
{
	SDL_Surface* screen = SDL_GetWindowSurface(m_window);
	return cairosdl_create (screen);
}