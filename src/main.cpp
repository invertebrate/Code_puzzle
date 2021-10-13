#include "code_puzzle.h"

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
		SDL_RenderCopy(this->game_renderer_get()->sdl_renderer, texture, NULL, object->sdl_rect_get());
		this->game_renderer_get()->render();
		(void)texture;
}

void GameManager::game_loop()
{
		SDL_Event e;
		int game_running = 1;
		this->game_object_create("default");
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

int main()
{
		GameManager *game_manager = game_init();
		game_manager->load_assets();
		game_manager->game_run();
		// game_cleanup();
		return (0);
}
