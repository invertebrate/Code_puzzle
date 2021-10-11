#include "code_puzzle.h"

SDL_Texture *load_texture(SDL_Renderer *renderer, const char *file)
{
		SDL_Texture *new_texture = NULL;
		SDL_Surface *loaded_surface = IMG_Load(file);
		if (loaded_surface == NULL)
				printf("unable to load the image %s! SDL_omage Error: %s\n", file, IMG_GetError());
		else
		{
				new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
				if (new_texture == NULL)
						printf("unable to create the texture from %s! SDL "
							   "Error: %s\n",
							   file, SDL_GetError());
		}
		SDL_FreeSurface(loaded_surface);
		return (new_texture);
}

void update_window(GameRenderer *renderer)
{
		(void)renderer;
}

void render_frame(GameRenderer *renderer, GameObject *object)
{
		SDL_Texture *texture;
		SDL_RenderClear(renderer->sdl_renderer);
		texture = object->texture_get();
		SDL_Rect dstrect;
		dstrect.x = 100;
		dstrect.y = 100;
		dstrect.h = 50;
		dstrect.w = 75;
		SDL_RenderCopy(renderer->sdl_renderer, texture, NULL, &dstrect);
		renderer->render();
}

void game_init(SDL_Window *window)
{
		(void)window;
}

// TODO: CREATE GAME MANAGER OBJECT LIST AND UTILITY FUNCTIONS
// MAKE RENDERER READ GAME OBJECT LIST FROM MANAGER AND RENDER OBJECTS
// MAKE MAIN GAME LOGIC MEMBER FUNCTIONS OF THE GAME MANAGER
void game_loop(GameRenderer *renderer)
{
		SDL_Event e;
		GameObject object;
		object.texture_set(renderer->texture_create(TEST_TEXTURE));
		// game_manager->add_object(object); // create a  gameobject vector in gamemanager
		int game_running = 1;
		while (game_running)
		{
				while (SDL_PollEvent(&e) != 0)
				{
						if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
								game_running = 0;
				}
				// handle_events();
				// input_script();
				// update_game_state();
				render_frame(renderer, &object);
		}
}

void game_run()
{
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); // error check these
		TTF_Init();
		SDL_Window *window = SDL_CreateWindow("test1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
		GameRenderer *renderer = new GameRenderer(window);
		game_init(window);
		game_loop(renderer);
}

int main()
{
		game_run();
		// game_cleanup();
		return (0);
}
