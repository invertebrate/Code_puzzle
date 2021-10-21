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

void GameManager::end_condition_check()
{
		int res = -1;
		for (int w = 0; w < this->game_grid_get()->grid_width_get(); w++)
		{
				for (int h = 0; h < this->game_grid_get()->grid_width_get(); h++)
				{
						game_grid_get()->operate_pairwise_at(lose_condition_check, {w, h}, &res);
						if (res == true)
						{
								printf("GAME OVER!\n");
						}
						res = -1;
						game_grid_get()->operate_pairwise_at(win_condition_check, {w, h}, &res);
						// printf("RES2: %d\n", res);

						if (res == true)
						{
								printf("GAME WON!\n");
						}
				}
		}
}
void GameManager::events_handle(SDL_Event *e)
{
		while (SDL_PollEvent(e) != 0)
		{
				if (e->type == SDL_QUIT || (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE))
						game_running = 0;
				else if ((e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_w))
				{
						player->move_to({player->coordinates_get().x, player->coordinates_get().y - 1});
				} // move up;
				else if ((e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_s))
				{
						player->move_to({player->coordinates_get().x, player->coordinates_get().y + 1});
				} // move down;
				else if ((e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_a))
				{
						player->move_to({player->coordinates_get().x - 1, player->coordinates_get().y});
				} // move left;
				else if ((e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_d))
				{
						player->move_to({player->coordinates_get().x + 1, player->coordinates_get().y});
				} // move right;
		}
}
void GameManager::game_state_update()
{
		end_condition_check();
}
void GameManager::game_loop()
{
		SDL_Event e;
		this->game_object_create(e_object_type_enemy);
		this->game_object_create(e_object_type_enemy_2);
		this->game_object_create(e_object_type_finish);

		while (game_running)
		{
				this->fps_start();
				///////GAME LOOP START
				events_handle(&e);

				game_state_update();
				// // handle_events();
				// // input_script();
				// // update_game_state();
				this->render_frame();
				//////GAME LOOP END
				this->fps_end();
		}
}

GameManager *game_manager_init()
{
		GameManager *game_manager;
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); // error check these
		TTF_Init();
		game_manager = new GameManager();
		game_manager->init();
		game_manager->game_grid_get()->texture_set(game_manager->game_renderer_get()->texture_create(GRID_TEXTURE));
		return (game_manager);
}
void GameManager::game_init()
{
		this->game_object_create(e_object_type_hero);
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
		GameManager *game_manager = game_manager_init();
		game_manager->load_assets();
		game_manager->game_init();
		game_manager->game_run();
		// game_cleanup();
		return (0);
}
