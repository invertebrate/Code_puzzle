#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "game_object.h"
#include "renderer.h"
#include "window.h"
#include <vector>

class GameManager
{
	  private:
		GameWindow *window;
		GameRenderer *renderer;
		std::vector<GameObject *> game_objects;

	  public:
		GameManager();
		~GameManager();
		GameRenderer *renderer_get();
};

#endif