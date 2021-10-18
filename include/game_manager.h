#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "game_object.h"
#include "grid.h"
#include "renderer.h"
#include "window.h"
#include <functional>
#include <map>
#include <vector>

#define WINDOW_SIZE 1800
#define GRID_WIDTH 900
#define GRID_HEIGHT 900
#define GRID_DIMENSIONS 10
#define GRID_SQR_SIZE 89

typedef std::function<void(GameObject *, GameObject *, void *)> f_gameobject_operation;
typedef std::function<void(GameObject *, GameObject *, void *, void *)> f_gameobject_operation_param;

enum e_object_type
{
		e_object_type_hero = 10,
		e_object_type_enemy = 11,
		e_object_type_enemy_2 = 12,
		e_object_type_finish = 13,
};

class GameGrid;

class GameManager
{
	  private:
		GameWindow *game_window;
		GameRenderer *game_renderer;
		GameGrid *game_grid;
		bool initialized = false;
		Vector2int window_size = {WINDOW_SIZE, WINDOW_SIZE};
		//--performance
		uint64_t fps_start_time;
		float delta_time;
		float ms_per_sec = 1000.0;
		uint64_t time_diff;
		float limiter = 0;
		//---
	  public:
		std::vector<GameObject *> game_objects;
		GameObject *player;
		int object_count = 0;
		std::map<const char *, SDL_Texture *> asset_textures;
		bool game_running = 1;
		GameManager();
		~GameManager();
		void init();
		void game_init();
		void load_assets();
		void game_state_update();
		GameRenderer *game_renderer_get();
		GameWindow *game_window_get();
		GameGrid *game_grid_get();
		void game_run();
		void game_loop();
		void events_handle(SDL_Event *e);
		void render_frame();
		void render_objects();
		void render_grid();
		uint32_t game_object_create(int type);
		void game_object_destroy();
		void fps_start();
		void fps_end();
		Vector2int window_size_get();
		void end_condition_check();
		static void win_condition_check(GameObject *obj1, GameObject *obj2, void *res);
		static void lose_condition_check(GameObject *obj1, GameObject *obj2, void *res);
};

// gameobjects should know where they are on the grid and grid should know what objects are on each slot
class GameGrid
{
	  private:
		uint32_t width = GRID_DIMENSIONS;
		uint32_t height = GRID_DIMENSIONS;
		uint32_t img_width = GRID_WIDTH;
		uint32_t img_height = GRID_HEIGHT;
		float grid_line_width = 0;

		std::map<uint32_t, std::vector<GameObject *> *> grid;
		SDL_Texture *sdl_texture;

	  public:
		GameGrid()
		{
				grid_line_width = (GRID_WIDTH - (width * GRID_SQR_SIZE)) / (width - 1);
				for (uint32_t h = 0; h < height; h++)
				{
						for (uint32_t w = 0; w < width; w++)
						{
								std::vector<GameObject *> *object_list =
									new std::vector<GameObject *>(); // kinda sus syntax bc of pointer
								auto pair = std::make_pair(w + h * width, object_list);
								grid.insert(pair); // hopefully this makes a map with coordinates as keys and an object
												   // vector as value
												   // test gameobject insertion and indexing works
						}
				}
		}
		~GameGrid();
		std::map<uint32_t, std::vector<GameObject *> *> *grid_get()
		{
				return (&grid);
		}
		void texture_set(SDL_Texture *texture)
		{
				sdl_texture = texture;
		}
		SDL_Texture *texture_get()
		{
				return (sdl_texture);
		}
		float line_width_get()
		{
				return (grid_line_width);
		}
		uint32_t grid_index_get(Vector2int coords)
		{
				return (coords.x + coords.y * width);
		}
		Vector2int grid_coords_get(uint32_t index)
		{
				Vector2int coords;

				coords.x = index % width;
				coords.y = index / width;
				return (coords);
		}
		void operate_on_objects_at(f_gameobject_operation f_operation, Vector2int coords, void *res)
		{
				int index = grid_index_get(coords);
				auto objects = grid.at(index);
				// printf("resolve objects at: %d %d\n", coords.x, coords.y);
				// printf("objects vector size: %lu\n", objects->size());
				for (uint32_t i = 0; i < objects->size() - 1; i++) // supposed to loop through object pairs without
																   // repetition
				{
						for (auto iterator = objects->begin() + i + 1; iterator != objects->end(); iterator++)
						{
								f_operation(objects->at(i), *iterator, res);
								// printf("Compared obj: %p to obj: %p\n with types: %d to %d\n", comp1, comp2,
								//    comp1->type_get(), comp2->type_get());
						}
				}
		}
		void operate_on_objects_at(f_gameobject_operation_param f_operation, Vector2int coords, void *param, void *res)
		{
				int index = grid_index_get(coords);
				auto objects = grid.at(index);
				// printf("resolve objects at: %d %d\n", coords.x, coords.y);
				// printf("objects vector size: %lu\n", objects->size());
				for (uint32_t i = 0; i < objects->size() - 1; i++) // supposed to loop through object pairs without
																   // repetition
				{
						for (auto iterator = objects->begin() + i + 1; iterator != objects->end(); iterator++)
						{
								f_operation(objects->at(i), *iterator, param, res);
								// printf("Compared obj: %p to obj: %p\n with types: %d to %d\n", comp1, comp2,
								//    comp1->type_get(), comp2->type_get());
						}
				}
		}
		void add_object_at(GameObject *obj, Vector2int coords)
		{
				auto objects = grid.at(grid_index_get(coords));
				objects->push_back(obj);
		}
		void remove_object_at(GameObject *obj, Vector2int coords)
		{
				auto objects = grid.at(grid_index_get(coords));
				for (auto it = objects->begin(); it != objects->end(); it++)
				{
						if ((*it) == obj)
								objects->erase(it);
				}
				objects->shrink_to_fit();
		}
};

#endif