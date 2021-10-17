#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "game_object.h"
#include "grid.h"
#include "renderer.h"
#include "window.h"
#include <map>
#include <vector>

#define WINDOW_SIZE 1800
#define GRID_WIDTH 900
#define GRID_HEIGHT 900
#define GRID_DIMENSIONS 10
#define GRID_SQR_SIZE 89

enum e_object_type
{
		e_object_type_hero = 0,
		e_object_type_enemy = 1
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
		std::map<const char *, SDL_Texture *> asset_textures;
		GameManager();
		~GameManager();
		void init();
		void load_assets();
		GameRenderer *game_renderer_get();
		GameWindow *game_window_get();
		GameGrid *game_grid_get();
		void game_run();
		void game_loop();
		void render_frame();
		uint32_t game_object_create(int type);
		void fps_start();
		void fps_end();
		Vector2int window_size_get();
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
								auto pair = std::make_pair(w + h * w, object_list);
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
};

#endif