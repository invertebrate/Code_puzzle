#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "game_object.h"
#include "renderer.h"
#include "window.h"
#include <vector>

class GameManager
{
	  private:
		GameWindow *game_window;
		GameRenderer *game_renderer;
		std::vector<GameObject *> game_objects;

	  public:
		GameManager();
		~GameManager();
		void init();
		GameRenderer *game_renderer_get();
		GameWindow *game_window_get();
		void game_run();
		void game_loop();
		void render_frame();
		uint32_t game_object_create(const char *type);
};

#endif