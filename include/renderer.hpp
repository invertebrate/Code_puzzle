#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class GameRenderer
{
	  public:
		SDL_Window *sdl_window;
		SDL_Renderer *sdl_renderer;

		GameRenderer(SDL_Window *window);
		~GameRenderer();
		void render();
		SDL_Texture *texture_load(const char *file);

	  private:
		GameRenderer(const GameRenderer &);
};
#endif