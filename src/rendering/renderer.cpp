
#include "renderer.hpp"

GameRenderer::GameRenderer(SDL_Window *window)
{
		sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		sdl_window = window;
		SDL_SetRenderDrawColor(sdl_renderer, 200, 100, 150, 255);
}

GameRenderer::~GameRenderer()
{
		SDL_DestroyRenderer(sdl_renderer);
}

void GameRenderer::render()
{
		SDL_RenderPresent(this->sdl_renderer);
}

SDL_Texture *GameRenderer::texture_load(const char *file)
{
		SDL_Texture *new_texture = NULL;
		SDL_Surface *loaded_surface = IMG_Load(file);
		if (loaded_surface == NULL)
				printf("unable to load the image %s! SDL_omage Error: %s\n", file, IMG_GetError());
		else
		{
				new_texture = SDL_CreateTextureFromSurface(sdl_renderer, loaded_surface);
				if (new_texture == NULL)
						printf("unable to create the texture from %s! SDL "
							   "Error: %s\n",
							   file, SDL_GetError());
		}
		SDL_FreeSurface(loaded_surface);
		return (new_texture);
}
