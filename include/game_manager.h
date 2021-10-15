#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "game_object.h"
#include "grid.h"
#include "renderer.h"
#include "window.h"
#include <map>
#include <vector>

#define WINDOW_SIZE 1000

class GameManager
{
	  private:
		GameWindow *game_window;
		GameRenderer *game_renderer;
		GameGrid *game_grid;
		std::vector<GameObject *> game_objects;
		bool initialized = false;
		Vector2 window_size = {WINDOW_SIZE, WINDOW_SIZE};
		//--performance
		uint64_t fps_start_time;
		float delta_time;
		float ms_per_sec = 1000.0;
		uint64_t time_diff;
		float limiter = 0;
		//---
	  public:
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
		uint32_t game_object_create(const char *type);
		void fps_start();
		void fps_end();
};

#endif