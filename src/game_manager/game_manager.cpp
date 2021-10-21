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
		tex = this->game_renderer_get()->texture_create(FINISH_TEXTURE);
		this->asset_textures.insert({FINISH_TEXTURE, tex});
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
		printf("Creating a game object of type %d\n", type);
		GameObject *object;
		object = NULL;
		if (type == e_object_type_hero)
		{
				object = GameObject::hero_object_create(this, object);
				object_count++;
				game_grid_get()->add_object_at(object, {0, 0});
				printf("create add ^ \n");
				// object->move_to(Vector2int{0, 0});

				player = object;
				return (e_object_type_hero);
		}
		if (type == e_object_type_enemy)
		{
				object = GameObject::enemy_object_create(this, object);
				game_grid_get()->add_object_at(object, {0, 0});
				object->move_to(Vector2int{3, 3});
				object_count++;
				return (e_object_type_enemy);
		}
		if (type == e_object_type_enemy_2)
		{
				object = GameObject::enemy_2_object_create(this, object);
				game_grid_get()->add_object_at(object, {0, 0});
				object->move_to(Vector2int{0, 0});
				object_count++;
				return (e_object_type_enemy);
		}
		if (type == e_object_type_finish)
		{
				object = GameObject::finish_object_create(this, object);
				game_grid_get()->add_object_at(object, {0, 0});
				object->move_to(Vector2int{9, 9});
				object_count++;
				return (e_object_type_finish);
		}
		return (0);
}
void GameManager::game_object_destroy()
{
		object_count--;
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
				// game_grid_get()->grid_objects_print();
				printf("fps: %f\n", 1000 / delta_time);
				this->player->move_to(player->coordinates_get() + Vector2int(1, 1));
				limiter = 0;
		}
}

Vector2int GameManager::window_size_get()
{
		return (window_size);
}
void GameManager::win_condition_check(GameObject *obj1, GameObject *obj2, void *res)
{
		if (*(int *)res == 1)
				return;
		if (obj1->type_get() == e_object_type_hero)
		{
				if (obj2->type_get() == e_object_type_finish)
				{
						*(int *)res = 1;
						return; // win;
				}
		}
		else if (obj2->type_get() == e_object_type_hero)
		{
				if (obj1->type_get() == e_object_type_finish)
				{
						*(int *)res = 1;
						return; // win;
				}
		}
		else
		{
				*(int *)res = 0;
				return;
		}
}
void GameManager::lose_condition_check(GameObject *obj1, GameObject *obj2, void *res)
{
		if (*(int *)res == 1)
				return;
		if (obj1->type_get() == e_object_type_hero)
		{
				// printf("obj1 was hero\n");
				if (obj2->type_get() == e_object_type_enemy || obj2->type_get() == e_object_type_enemy_2)
				{

						*(int *)res = 1;
						return;
						// lose;
				}
		}
		else if (obj2->type_get() == e_object_type_hero)
		{

				if (obj1->type_get() == e_object_type_enemy || obj1->type_get() == e_object_type_enemy_2)
				{
						*(int *)res = 1;
						return;
						// lose;
				}
		}
		else
		{
				*(int *)res = 0;
				return;
		}
}