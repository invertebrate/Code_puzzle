#include "code_puzzle.h"

void update_window(GameRenderer *renderer)
{
		(void)renderer;
}

void GameManager::render_frame()
{
		SDL_Texture *texture_grid;
		SDL_Texture *texture_hero;
		SDL_Texture *texture_enemy;

		SDL_RenderClear(this->game_renderer_get()->sdl_renderer);

		texture_grid = game_grid->texture_get();
		SDL_RenderCopy(this->game_renderer_get()->sdl_renderer, texture_grid, NULL, NULL);

		GameObject *object_hero = this->game_objects[0];
		GameObject *object_enemy = this->game_objects[1];
		texture_hero = object_hero->texture_get();
		texture_enemy = object_enemy->texture_get();
		SDL_RenderCopy(this->game_renderer_get()->sdl_renderer, texture_hero, NULL, object_hero->sdl_rect_get());
		SDL_RenderCopy(this->game_renderer_get()->sdl_renderer, texture_enemy, NULL, object_enemy->sdl_rect_get());
		this->game_renderer_get()->render();
}

void GameManager::game_loop()
{
		SDL_Event e;
		int game_running = 1;
		int obj = this->game_object_create(e_object_type_hero);
		this->game_object_create(e_object_type_enemy);
		printf("created object %d\n", obj);
		// auto pair = std::make_pair(0, 5);
		game_grid->grid_get()->find(5)->second->push_back(game_objects[0]);
		game_grid->grid_get()->find(5)->second->at(0)->print();
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
// CREATE A 2D GRID CLASS AND CUNTIONALITY
// ADD OBJECT MANIPULATION FUNCTIONS
// CREATE SUPPORT FOR MULTIPLE OBJECT RENDERING
int main()
{
		GameManager *game_manager = game_init();
		game_manager->load_assets();
		game_manager->game_run();
		// game_cleanup();
		return (0);
}
