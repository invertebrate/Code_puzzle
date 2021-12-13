#include "code_puzzle.hpp"

void update_window(GameRenderer *renderer)
{
		(void)renderer;
}

GameManager *game_manager_init()
{
		GameManager *game_manager;
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
		TTF_Init();
		game_manager = new GameManager();
		game_manager->init();
		game_manager->game_grid_get()->texture_set(game_manager->game_renderer_get()->texture_create(GRID_TEXTURE));
		return (game_manager);
}

int main()
{
		GameManager *game_manager = game_manager_init();
		game_manager->load_assets();
		game_manager->game_init();
		game_manager->game_run();
		// game_cleanup();
		return (0);
}

// TODO!
// Game start, game end, paused states
// Static obstacles >> 0.1 done
// Dynamic obstacles -create step resolve priority so obstacles are resolved first
// More complex enemy behaviour
// Pathfinding for enemies?
// Turn based command reading -adds comments after command lines for executed commands<- >> 0.7 done
//
// MID-PROJECT PROJECT
//	DIJKSTRA's pathfinding algorithm
//