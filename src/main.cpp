#include "code_puzzle.hpp"

void update_window(GameRenderer *renderer)
{
		(void)renderer;
}

GameManager *game_manager_init()
{
		GameManager *game_manager;
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); // error check these
		TTF_Init();
		game_manager = new GameManager();
		game_manager->init();
		game_manager->game_grid_get()->texture_set(game_manager->game_renderer_get()->texture_create(GRID_TEXTURE));
		return (game_manager);
}

// TODO:
// REFACTOR OBJECT CREATION FUNCTIONS
// CREATE OBJECT "AI" SOLVER
// CREATE OBJECT "AI" FUNCTIONALITY
// CREATE SIMPLE GAME OVER STATE AND RESET FUNCTIONALITY---
// ADD OBJECT INTERACTION FUNCTIONS
// IMPLEMENT LUA INTEGRATION
///// -MAKE A SETTINGS FILE FROM WHICH GAME SETTINGS ARE READ
///// -CREATE INTERFACE FROM A LUA FILE THAT DRIVES GAME OBJECTS
///// -CREATE A WRAPPER FOR THE "LUA CODING GAME LANGUAGE"
int main()
{
		settings_parse(NULL, "settings.lua");
		GameManager *game_manager = game_manager_init();
		game_manager->load_assets();
		game_manager->game_init();
		game_manager->game_run();
		// game_cleanup();
		return (0);
}
