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

void GameManager::render_frame()
{
		SDL_Texture *texture;
		SDL_RenderClear(this->game_renderer_get()->sdl_renderer);
		GameObject *object = this->game_objects[0];
		texture = object->texture_get();
		// // texture = this->game_renderer_get()->texture_create(TEST_TEXTURE);
		// SDL_Rect dstrect;
		// dstrect.x = 100;
		// dstrect.y = 100;
		// dstrect.h = 50;
		// dstrect.w = 75;
		SDL_RenderCopy(this->game_renderer_get()->sdl_renderer, texture, NULL, object->sdl_rect_get());
		this->game_renderer_get()->render();
		// (void)dstrect;
		// (void)index;
		(void)texture;
}

uint64_t performance_counter_start(void)
{
		return (SDL_GetPerformanceCounter());
}

void GameManager::game_loop()
{
		SDL_Event e;
		uint64_t start_time;
		float delta_time;
		float ms_per_sec;
		uint64_t time_diff;
		float limiter = 0;

		ms_per_sec = 1000.0;

		// object->texture_set(game_renderer->texture_create(TEST_TEXTURE));
		// game_manager->add_object(object); // create a  gameobject vector in gamemanager
		int game_running = 1;

		this->game_object_create("default");

		while (game_running)
		{
				start_time = performance_counter_start();

				///////GAME LOOP START
				while (SDL_PollEvent(&e) != 0)
				{
						if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
								game_running = 0;
				}
				// // handle_events();
				// // input_script();
				// // update_game_state();
				this->render_frame();
				//////GAME LOOP END

				time_diff = SDL_GetPerformanceCounter() - start_time;
				delta_time = (float)time_diff * ms_per_sec / (float)SDL_GetPerformanceFrequency();
				limiter += delta_time;
				if (limiter > 1000)
				{
						printf("fps: %f\n", 1000 / delta_time);
						limiter = 0;
				}
		}
}

GameManager *game_init(GameManager *game_manager)
{
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); // error check these
		TTF_Init();
		game_manager = new GameManager();
		game_manager->init();
		return (game_manager);
}

void GameManager::game_run()
{
		this->game_loop();
}

// TODO: CREATE GAME MANAGER OBJECT LIST AND UTILITY FUNCTIONS
// MAKE RENDERER READ GAME OBJECT LIST FROM MANAGER AND RENDER OBJECTS
// MAKE MAIN GAME LOGIC MEMBER FUNCTIONS OF THE GAME MANAGER
// CREATE ASSET LOADING SYSTEM THAT IS NOT RUNTIME!
int main()
{
		GameManager *game_manager;

		game_manager = NULL;
		game_manager = game_init(game_manager);
		game_manager->game_run();
		// game_cleanup();
		return (0);
}
