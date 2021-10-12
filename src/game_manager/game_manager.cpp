#include "game_manager.h"
#include "code_puzzle.h"
#include <unistd.h>

GameManager::GameManager()
{
}
GameManager::~GameManager()
{
}
void GameManager::init()
{
		game_window = new GameWindow("game_window", 1000, 1000);
		game_renderer = new GameRenderer(game_window->sdl_window_get());
}
GameRenderer *GameManager::game_renderer_get()
{
		return (game_renderer);
}
GameWindow *GameManager::game_window_get()
{
		return (game_window);
}
uint32_t GameManager::game_object_create(const char *type)
{
		GameObject *object;
		if (!strcmp(type, "default"))
		{
				object = new GameObject(this, TEST_TEXTURE, Vector2(200, 200), Vector2(0.0, 0.0));
				game_objects.push_back(object);
				return (game_objects.size() - 1);
		}
		return (0);
		(void)object;
}
