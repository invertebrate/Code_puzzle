#include "code_puzzle.h"

void update_window(GameRenderer *renderer)
{
		(void)renderer;
}

void GameManager::render_objects()
{
		for (auto iterator = game_objects.begin(); iterator != game_objects.end(); iterator++)
		{
				SDL_Texture *tex;
				GameObject *obj;
				obj = *iterator;
				tex = obj->texture_get();
				SDL_RenderCopy(this->game_renderer_get()->sdl_renderer, tex, NULL, obj->sdl_rect_get());
		}
}
void GameManager::render_grid()
{
		SDL_Texture *texture_grid;
		texture_grid = game_grid->texture_get();
		SDL_RenderCopy(this->game_renderer_get()->sdl_renderer, texture_grid, NULL, NULL);
}
void GameManager::render_frame()
{
		SDL_RenderClear(this->game_renderer_get()->sdl_renderer);
		render_grid();
		render_objects();
		this->game_renderer_get()->render();
}

void GameManager::game_loop()
{
		SDL_Event e;
		int game_running = 1;
		int obj = this->game_object_create(e_object_type_hero);
		(void)obj;
		this->game_object_create(e_object_type_enemy);
		this->game_object_create(e_object_type_enemy_2);

		game_grid_get()->resolve_objects_at({0, 0});
		while (game_running)
		{
				this->fps_start();
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
				this->fps_end();
		}
}

GameManager *game_init()
{
		GameManager *game_manager;
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); // error check these
		TTF_Init();
		game_manager = new GameManager();
		game_manager->init();
		game_manager->game_grid_get()->texture_set(game_manager->game_renderer_get()->texture_create(GRID_TEXTURE));
		return (game_manager);
}

void GameManager::game_run()
{
		this->game_loop();
}

// TODO: CREATE GAME MANAGER OBJECT LIST AND UTILITY FUNCTIONS
// MAKE RENDERER READ GAME OBJECT LIST FROM MANAGER AND RENDER OBJECTS
// ADD OBJECT MANIPULATION FUNCTIONS
int main()
{
		GameManager *game_manager = game_init();
		game_manager->load_assets();
		game_manager->game_run();
		// game_cleanup();
		return (0);
}
