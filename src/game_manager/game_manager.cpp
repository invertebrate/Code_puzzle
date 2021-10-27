#include "game_manager.hpp"
#include "ai_object.hpp"
#include "code_puzzle.hpp"
#include "events.hpp"
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
		settings_read(this, SETTINGS_FILE);
		game_window = new GameWindow("game_window", window_size.x, window_size.y);
		game_renderer = new GameRenderer(game_window->sdl_window_get());
		game_grid = new GameGrid(this);
		custom_event_type = SDL_RegisterEvents(1);
		custom_event_handles_register();
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
uint32_t GameManager::game_object_create(e_object_type type)
{
		printf("Creating a game object of type %d\n", type);
		GameObject *object;
		object = NULL;
		if (type == e_object_type_hero)
		{
				object = GameObject::hero_object_create(this, object);
				object->type_set(type);
				object_count++;
				game_grid_get()->add_object_at(object, {0, 0});
				player = object;
				return (e_object_type_hero);
		}
		if (type == e_object_type_enemy)
		{
				object = GameObject::enemy_object_create(this, object);
				object->type_set(type);
				game_grid_get()->add_object_at(object, {0, 0});
				object->move_to(Vector2int{3, 3});
				object_count++;
				return (e_object_type_enemy);
		}
		if (type == e_object_type_enemy_2)
		{
				Vector2int *patrol_path = (Vector2int *)malloc(sizeof(Vector2int) * 2);
				patrol_path[0] = {2, 2};
				patrol_path[1] = {5, 5};
				object = GameObject::enemy_2_object_create(this, object);
				object->type_set(type);
				object->ai_object = new AIObject(object, e_behaviour_type_follow, patrol_path);
				game_grid_get()->add_object_at(object, {0, 0});
				object->move_to(Vector2int{3, 1});
				object_count++;
				return (e_object_type_enemy);
		}
		if (type == e_object_type_finish)
		{
				object = GameObject::finish_object_create(this, object);
				object->type_set(type);
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
void GameManager::grid_size_set(Vector2int size)
{
		this->grid_size = size;
}
Vector2int GameManager::grid_size_get()
{
		return (this->grid_size);
}
void GameManager::window_size_set(Vector2int size)
{
		this->window_size = size;
}
Vector2int GameManager::window_size_get()
{
		return (this->window_size);
}
void GameManager::step_time_set(float step)
{
		this->step_time = step;
}
float GameManager::step_time_get()
{
		return (this->step_time);
}
void GameManager::fps_cap_set(int cap)
{
		this->target_fps = cap;
}
int GameManager::fps_cap_get()
{
		return (this->target_fps);
}
void GameManager::fps_start()
{
		fps_start_time = SDL_GetPerformanceCounter();
}
void GameManager::fps_end()
{
		static float timer = 0;

		limit_fps();
		time_diff = SDL_GetPerformanceCounter() - fps_start_time;
		delta_time = (float)time_diff * ms_per_sec / (float)SDL_GetPerformanceFrequency();
		timer += ms_per_sec / target_fps;
		if (timer > ms_per_sec)
		{
				// game_grid_get()->grid_objects_print();
				printf("fps: %f / %f\n", ms_per_sec / delta_time, target_fps);
				timer = 0;
				for (auto it = this->game_objects.begin(); it != this->game_objects.end(); it++)
				{
						if ((*it)->type_get() == e_object_type_enemy_2)
						{
								(*it)->ai_object->position_resolve();
						}
				}
		}
}
void GameManager::limit_fps()
{
		float wait = ms_per_sec / target_fps;
		time_diff = SDL_GetPerformanceCounter() - fps_start_time;
		delta_time = (float)time_diff * ms_per_sec / (float)SDL_GetPerformanceFrequency();
		wait -= delta_time;
		if (wait > 0)
		{
				SDL_Delay(wait);
		}
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
								// printf("GAME OVER!\n");
								custom_event_add(e_event_code_gamelost, NULL, NULL);
						}
						res = -1;
						game_grid_get()->operate_pairwise_at(win_condition_check, {w, h}, &res);

						if (res == true)
						{
								custom_event_add(e_event_code_gamewon, NULL, NULL);

								// printf("GAME WON!\n");
						}
				}
		}
}

void GameManager::custom_event_handles_register()
{
		auto pair = std::make_pair(e_event_code_gamewon, game_won);
		custom_events.insert(pair);
		pair = std::make_pair(e_event_code_gamelost, game_lost);
		custom_events.insert(pair);
}

void GameManager::custom_event_handle(SDL_Event *event)
{
		auto handle = custom_events.find((e_event_code)event->user.code);
		handle->second(event->user.data1, event->user.data2);
}

void GameManager::custom_event_add(e_event_code event_code, void *data1, void *data2)
{
		if (custom_event_type != ((Uint32)-1))
		{
				SDL_Event event;
				SDL_memset(&event, 0, sizeof(event));
				event.type = custom_event_type;
				event.user.code = event_code;
				event.user.data1 = data1;
				event.user.data2 = data2;
				SDL_PushEvent(&event);
		}
}

void GameManager::events_handle(SDL_Event *e)
{
		while (SDL_PollEvent(e) != 0)
		{
				if (e->type == SDL_USEREVENT)
						custom_event_handle(e);
				else if (e->type == SDL_QUIT || (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE))
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
void GameManager::game_init()
{
		this->game_object_create(e_object_type_hero);
}
void GameManager::game_run()
{
		commands_read(this, F_COMMANDS_FILE);
		this->game_loop();
}
void GameManager::game_state_update()
{
		end_condition_check();
}
void GameManager::game_loop()
{
		SDL_Event e;
		// this->game_object_create(e_object_type_enemy);
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

GameGrid::GameGrid(GameManager *manager)
{
		if (manager->grid_size_get() >= (Vector2int){1, 1})
		{
				width = manager->grid_size_get().x;
				height = manager->grid_size_get().y;
		}
		if (manager->window_size_get() >= (Vector2int){1, 1})
		{
				// img_width = manager->window_size_get().x;
				// img_height = manager->window_size_get().y;
				;
		}
		if (manager->grid_size_get() >= (Vector2int){1, 1})
		{

				;
		}
		grid_line_width = (img_width - (width * grid_sqr_size)) / (width - 1);
		for (uint32_t h = 0; h < height; h++)
		{
				for (uint32_t w = 0; w < width; w++)
				{
						std::vector<GameObject *> *object_list = new std::vector<GameObject *>();
						auto pair = std::make_pair(w + h * width, object_list);
						grid.insert(pair);
				}
		}
}
std::map<uint32_t, std::vector<GameObject *> *> *GameGrid::grid_get()
{
		return (&grid);
}
void GameGrid::texture_set(SDL_Texture *texture)
{
		sdl_texture = texture;
}
SDL_Texture *GameGrid::texture_get()
{
		return (sdl_texture);
}
float GameGrid::line_width_get()
{
		return (grid_line_width);
}
int GameGrid::grid_width_get()
{
		return (width);
}
int GameGrid::grid_height_get()
{
		return (height);
}
uint32_t GameGrid::grid_index_get(Vector2int coords)
{
		return (coords.x + coords.y * width);
}
Vector2int GameGrid::grid_coords_get(uint32_t index)
{
		Vector2int coords;

		coords.x = index % width;
		coords.y = index / width;
		return (coords);
}
void GameGrid::operate_pairwise_at(f_gameobject_operation f_operation, Vector2int coords, void *res)
{
		int index = grid_index_get(coords);
		auto objects = grid.at(index);
		if (objects->size() < 1)
				return;
		for (uint32_t i = 0; i < objects->size() - 1; i++) // supposed to loop through object pairs without
														   // repetition
		{
				for (auto iterator = objects->begin() + i + 1; iterator != objects->end(); iterator++)
				{
						f_operation(objects->at(i), *iterator, res);
				}
		}
}
void GameGrid::operate_pairwise_at(f_gameobject_operation_param f_operation, Vector2int coords, void *param, void *res)
{
		int index = grid_index_get(coords);
		auto objects = grid.at(index);
		for (uint32_t i = 0; i < objects->size() - 1; i++) // supposed to loop through object pairs without
														   // repetition
		{
				for (auto iterator = objects->begin() + i + 1; iterator != objects->end(); iterator++)
				{
						f_operation(objects->at(i), *iterator, param, res);
				}
		}
}
void GameGrid::add_object_at(GameObject *obj, Vector2int coords)
{
		auto objects = grid.at(grid_index_get(coords));
		objects->push_back(obj);
}
void GameGrid::remove_object_at(GameObject *obj, Vector2int coords)
{
		auto objects = grid.at(grid_index_get(coords));
		if (objects->size() > 0)
		{
				objects->erase(std::remove(objects->begin(), objects->end(), obj), objects->end());
		}
}
uint32_t GameGrid::grid_sqr_size_get()
{
		return (grid_sqr_size);
}
uint32_t GameGrid::img_width_get()
{
		return (img_width);
}
uint32_t GameGrid::img_height_get()
{
		return (img_height);
}
void GameGrid::grid_objects_print()
{
		printf("PRINTING OBJECTS:++++++++++++++++++++++++\n");

		for (uint32_t i = 0; i < width * height - 1; i++)
		{
				if (grid.at(i)->size() > 0)
				{
						for (auto it = grid.at(i)->begin(); it != grid.at(i)->end(); it++)
						{
								printf("object at %d %d: \n", grid_coords_get(i).x, grid_coords_get(i).y);
								(*it)->print();
						}
				}
				else
						printf("NO OBJECTS AT %d %d: \n", grid_coords_get(i).x, grid_coords_get(i).y);
		}
		printf("END OF PRINT========================\n");
}