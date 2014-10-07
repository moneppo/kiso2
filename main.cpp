#include "SDLWindow.h"
#include "KisoApp.h"
#include "KisoRenderer.h"
#include <string>
#include <iostream>

using namespace std;

int width = 800;
int height = 600;

int main() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		return 1;
	}
	SDLWindow sdl = SDLWindow();
	KisoRenderer renderer = KisoRenderer();
	KisoApp theApp("foo", "bar");
	
	theApp.startVM();
	SDL_Event event[1];

	bool running = true;
	while(running) {
		
		while (SDL_PollEvent (event)) {
			switch (event->type) {
				case SDL_KEYDOWN:
					if (event->key.keysym.sym == SDLK_q)
						running = false;
					break;
				case SDL_QUIT:
					running = false;
					break;
			}
		}

		//while (SDL_LockSurface (screen) != 0) {
		//	SDL_Delay (1);
		//}
		cairo_t *cr = sdl.getCairo();
		renderer.queueRender( cr, &theApp);
		cairo_destroy (cr);
		//SDL_UnlockSurface (screen);
	}
}