
#ifndef CODE_PUZZLE_H
# define CODE_PUZZLE_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include <stdio.h>
# include <math.h>
# include "window.h"
# include "renderer.h"
# include "vector.h"

# define TEST_TEXTURE "assets/test_texture.png"

class GameManager
{
	private:
	// GameWindow		*window;
	// GameRenderer	*renderer;
	public:
	GameManager()
	{
		// window = new GameWindow("test", 1000, 1000);
		// renderer = new GameRenderer(window->get_window());
	}
};

#endif