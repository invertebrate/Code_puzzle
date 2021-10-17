#include "game_manager.h"
#include "code_puzzle.h"
#include <unistd.h>

GameManager::GameManager()
{
}
GameManager::~GameManager()
{
		if (initialized == true)
		{
				delete game_window;
				delete game_renderer;
				asset_textures.clear();
				game_objects.clear();
		}
}
void GameManager::init()
{
		game_window = new GameWindow("game_window", window_size.x, window_size.y);
		game_renderer = new GameRenderer(game_window->sdl_window_get());
		game_grid = new GameGrid();
		initialized = true;
}
void GameManager::load_assets()
{
		SDL_Texture *tex;
		tex = this->game_renderer_get()->texture_create(TEST_TEXTURE);
		this->asset_textures.insert({TEST_TEXTURE, tex});
		tex = this->game_renderer_get()->texture_create(
			HERO_TEXTURE); // shouldnt cause memory leaks bc .insert allocates and deallocates
		this->asset_textures.insert({HERO_TEXTURE, tex});
		tex = this->game_renderer_get()->texture_create(ENEMY_TEXTURE);
		this->asset_textures.insert({ENEMY_TEXTURE, tex});
}
GameRenderer *GameManager::game_renderer_get()
{
		return (game_renderer);
}
GameWindow *GameManager::game_window_get()
{
		return (game_window);
}
uint32_t GameManager::game_object_create(int type)
{
		GameObject *object;
		object = NULL;
		if (type == e_object_type_hero)
		{
				object = GameObject::hero_object_create(this, object);
				return (e_object_type_hero);
		}
		if (type == e_object_type_enemy)
		{
				object = GameObject::enemy_object_create(this, object);
				object->move_to(Vector2int{3, 3});
				return (e_object_type_enemy);
		}
		return (0);
}

GameGrid *GameManager::game_grid_get()
{
		return (game_grid);
}

void GameManager::fps_start()
{
		fps_start_time = SDL_GetPerformanceCounter();
}

void GameManager::fps_end()
{
		time_diff = SDL_GetPerformanceCounter() - fps_start_time;
		delta_time = (float)time_diff * ms_per_sec / (float)SDL_GetPerformanceFrequency();
		limiter += delta_time;
		if (limiter > 1000)
		{
				printf("fps: %f\n", 1000 / delta_time);
				limiter = 0;
		}
}

Vector2int GameManager::window_size_get()
{
		return (window_size);
}