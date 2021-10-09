#ifndef RENDERER_H
# define RENDERER_H

# include "code_puzzle.h"

class	GameRenderer
{
	public:
		SDL_Window		*sdl_window;
		SDL_Renderer	*sdl_renderer;
		GameRenderer(SDL_Window *window);
		~GameRenderer();
		void	render();
	private:
		GameRenderer(const GameRenderer&);
};
#endif