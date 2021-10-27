#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "game_object.hpp"
#include "grid.hpp"
#include "lua_app.hpp"
#include "renderer.hpp"
#include "window.hpp"
#include <algorithm>
#include <functional>
#include <map>
#include <vector>

#define TEST_TEXTURE "assets/test_texture.png"
#define HERO_TEXTURE "assets/hero.png"
#define ENEMY_TEXTURE "assets/enemy.png"
#define GRID_TEXTURE "assets/grid.png"
#define FINISH_TEXTURE "assets/finish.png"
#define SETTINGS_FILE "settings.lua"

#define WINDOW_SIZE 1800
#define GRID_WIDTH 900
#define GRID_HEIGHT 900
#define GRID_DIMENSIONS_X 10
#define GRID_DIMENSIONS_Y 10
#define GRID_SQR_SIZE 89
#define TARGET_FPS 60

typedef std::function<void(GameObject *, GameObject *, void *)> f_gameobject_operation;
typedef std::function<void(GameObject *, GameObject *, void *, void *)> f_gameobject_operation_param;

enum e_object_type : unsigned int
{
		e_object_type_null = 10,
		e_object_type_hero = 11,
		e_object_type_enemy = 12,
		e_object_type_enemy_2 = 13,
		e_object_type_finish = 14,
};

enum e_event_code
{
		e_event_code_gamewon = 100,
		e_event_code_gamelost = 101
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
		Vector2int grid_size = {GRID_DIMENSIONS_X, GRID_DIMENSIONS_Y};
		float step_time;
		uint32_t custom_event_type = 0;
		std::map<e_event_code, void *(*)(void *, void *)> custom_events;
		//--performance
		float target_fps = TARGET_FPS;
		uint64_t fps_start_time;
		float delta_time;
		float ms_per_sec = 1000.0;
		uint64_t time_diff;
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
		void grid_size_set(Vector2int size);
		Vector2int grid_size_get();
		void window_size_set(Vector2int size);
		Vector2int window_size_get();
		void step_time_set(float step);
		float step_time_get();
		void fps_cap_set(int cap);
		int fps_cap_get();
		void game_run();
		void game_loop();
		void custom_event_handles_register();
		void custom_event_add(e_event_code event_code, void *data1, void *data2);
		void events_handle(SDL_Event *e);
		void custom_event_handle(SDL_Event *event);
		void render_frame();
		void render_objects();
		void render_grid();
		uint32_t game_object_create(e_object_type type);
		void game_object_destroy();
		void fps_start();
		void fps_end();
		void limit_fps();
		void end_condition_check();
		static void win_condition_check(GameObject *obj1, GameObject *obj2, void *res);
		static void lose_condition_check(GameObject *obj1, GameObject *obj2, void *res);
};

// gameobjects should know where they are on the grid and grid should know what objects are on each slot
class GameGrid
{
	  private:
		uint32_t width = GRID_DIMENSIONS_X;
		uint32_t height = GRID_DIMENSIONS_Y;
		uint32_t img_width = GRID_WIDTH;
		uint32_t img_height = GRID_HEIGHT;
		float grid_line_width = 0;
		uint32_t grid_sqr_size = GRID_SQR_SIZE;

		std::map<uint32_t, std::vector<GameObject *> *> grid;
		SDL_Texture *sdl_texture;

	  public:
		GameGrid(GameManager *manager);
		~GameGrid();
		std::map<uint32_t, std::vector<GameObject *> *> *grid_get();
		void texture_set(SDL_Texture *texture);
		SDL_Texture *texture_get();
		float line_width_get();
		int grid_width_get();
		int grid_height_get();
		uint32_t grid_index_get(Vector2int coords);
		Vector2int grid_coords_get(uint32_t index);
		void operate_pairwise_at(f_gameobject_operation f_operation, Vector2int coords, void *res);
		void operate_pairwise_at(f_gameobject_operation_param f_operation, Vector2int coords, void *param, void *res);
		void add_object_at(GameObject *obj, Vector2int coords);
		void remove_object_at(GameObject *obj, Vector2int coords);
		uint32_t grid_sqr_size_get();
		uint32_t img_width_get();
		uint32_t img_height_get();

		void grid_objects_print();
};

#endif