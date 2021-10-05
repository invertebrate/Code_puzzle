#ifndef WINDOW_H
# define WINDOW_H

# include "code_puzzle.h"

class window
{
	/*SDL_Texture		*frame;
	t_framebuffer	*framebuffer;
	TTF_Font		*main_font;
	TTF_Font		*small_font;
	TTF_Font		*title_font;
	int32_t			width;
	int32_t			height;
	int32_t			pitch;

	uint32_t		window_id;
	t_bool			is_hidden;
	t_bool			is_fullscreen;*/
	SDL_Window		*sdl_window;
	public:
		window(const char *name, int32_t width, int32_t height)
		{
			sdl_window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED, width, height, 0);
		}
	private:
};

class renderer
{

};



#endif