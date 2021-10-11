#include "game_manager.h"

GameManager::GameManager()
{
		window = new GameWindow("test", 1000, 1000);
		renderer = new GameRenderer(window->get_window());
}
GameManager::~GameManager()
{
}
GameRenderer *GameManager::renderer_get()
{
		return (renderer);
}