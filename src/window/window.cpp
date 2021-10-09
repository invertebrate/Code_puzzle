// #include "window.h"
// typedef struct s_window
// {
// 	SDL_Renderer			*renderer;
// 	SDL_Texture				*frame;
// 	t_framebuffer			*framebuffer;
// 	t_framebuffer			*framebuffer_3d;
// 	t_vec2					view_3d_pos;
// 	TTF_Font				*main_font;
// 	TTF_Font				*small_font;
// 	TTF_Font				*title_font;
// 	int32_t					width;
// 	int32_t					height;
// 	int32_t					pitch;
// 	t_bool					resized;
// 	SDL_Window				*window;
// 	uint32_t				window_id;
// 	t_bool					is_hidden;
// 	t_bool					is_fullscreen;
// }							t_window;

/*
** Clear frame
*/

// void	window_frame_clear(t_window *window, uint32_t clear_color)
// {
// 	l3d_buffer_uint32_clear(window->framebuffer->buffer,
// 		window->framebuffer->width * window->framebuffer->height, clear_color);
// }

// /*
// ** Draw window frame onto window
// */

// void	draw_window_frame(t_window *window)
// {
// 	SDL_UpdateTexture(window->frame, NULL, window->framebuffer->buffer,
// 		window->framebuffer->width * 4);
// 	SDL_RenderCopy(window->renderer, window->frame, NULL, NULL);
// 	SDL_RenderPresent(window->renderer);
// }

// void	window_3d_framebuffer_recreate(t_window *window, int32_t dims[2],
// 			int32_t pos[2])
// {
// 	error_check(dims[0] % 4 != 0 || dims[1] % 4 != 0,
// 		"3d framebuffer dimensions invalid. It should be dividible by 4");
// 	l3d_framebuffer_recreate(&window->framebuffer_3d, dims[0], dims[1]);
// 	window->view_3d_pos[0] = pos[0];
// 	window->view_3d_pos[1] = pos[1];
// }

// /*
// ** Create frame after e.g. resize
// */

// void	window_frame_recreate(t_window *window)
// {
// 	if (window->frame != NULL)
// 		SDL_DestroyTexture(window->frame);
// 	window->frame = SDL_CreateTexture(window->renderer,
// 			PIXEL_FORMAT, SDL_TEXTUREACCESS_STREAMING, window->width,
// 			window->height);
// 	error_check(window->frame == NULL, SDL_GetError());
// 	l3d_framebuffer_recreate(&window->framebuffer,
// 		window->width, window->height);
// }


// /*
// ** Create new window with framebuffers
// */

// void	window_create(t_window **window_ref,
// 			int32_t width, int32_t height)
// {
// 	t_window	*window;

// 	error_check((window = (t_window *)calloc(sizeof(t_window))) == NULL,
// 		"Window ft_calloc failed");
// 	window->window = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED,
// 			SDL_WINDOWPOS_CENTERED, width, height, 0);
// 	window->width = width;
// 	window->height = height;
// 	error_check(window->window == NULL, SDL_GetError());
// 	window->renderer
// 		= SDL_CreateRenderer(window->window, -1, SDL_RENDERER_SOFTWARE);
// 	error_check(window->renderer == NULL, SDL_GetError());
// 	window->window_id = SDL_GetWindowID(window->window);
// 	window->is_hidden = false;
// 	window->frame = NULL;
// 	window->framebuffer = NULL;
// 	window->framebuffer_3d = NULL;
// 	window_frame_recreate(window);
// 	SDL_AddEventWatch(window_resize_callback, window);
// 	window->resized = false;
// 	window->is_fullscreen = false;
// 	*window_ref = window;
// }

// /*
// ** Destroy window
// */

// void	window_destroy(t_window *window)
// {
// 	l3d_framebuffer_destroy(window->framebuffer);
// 	l3d_framebuffer_destroy(window->framebuffer_3d);
// 	SDL_DestroyRenderer(window->renderer);
// 	SDL_DestroyWindow(window->window);
// 	TTF_CloseFont(window->main_font);
// 	TTF_CloseFont(window->small_font);
// 	TTF_CloseFont(window->title_font);
// 	free(window);
// }
