
#include "renderer.h"

GameRenderer::GameRenderer(SDL_Window *window)
{

	sdl_renderer = SDL_CreateRenderer(window, -1,
					SDL_RENDERER_ACCELERATED);
	sdl_window = window;
	SDL_SetRenderDrawColor(sdl_renderer, 200, 100, 150, 255);
	printf("Renderer initialized!\n");
}

GameRenderer::~GameRenderer()
{

}

void	GameRenderer::render()
{
	SDL_RenderPresent(this->sdl_renderer);
}

