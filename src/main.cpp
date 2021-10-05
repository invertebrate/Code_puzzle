#include "code_puzzle.h"

void	game_init()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); //error check these
	TTF_Init();
}

void	game_loop()
{
	int game_running = 1;
	window *window1 = new window("test", 1000, 1000);
		(void)window1;
	while(game_running)
	{
		// handle_events();
		// input_script();
		// update_game_state();
		// render_frame();
	}
}

void	game_run()
{
	game_init();
	game_loop();
}

int		main()
{
	game_run();
	// game_cleanup();
	printf("run\n");
	return (0);
}



// void	doom3d_run(t_doom3d *app)
// {
// 	int32_t	cpu_count;
// 	int32_t	num_threads;

// 	assets_load(app);
// 	cpu_count = SDL_GetCPUCount();
// 	num_threads = ft_max_int((int32_t[2]){
// 			NUM_THREADS_DEFAULT, cpu_count}, 2);
// 	app->thread_pool = thread_pool_create(num_threads);
// 	LOG_INFO("Created thread pool with %d threads for %d logical cpus",
// 		num_threads, cpu_count);
// 	LOG_INFO("Initialize SDL");
// 	error_check(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0, SDL_GetError());
// 	error_check(TTF_Init() == -1, TTF_GetError());
// 	LOG_INFO("Initialize App settings");
// 	settings_init(app);
// 	LOG_INFO("Create SDL Window & frame buffers");
// 	window_create(&app->window, app->settings.width, app->settings.height);
// 	window_set_fonts(app->window, &app->assets);
// 	app_init(app);
// 	main_loop(app);
// 	cleanup(app);
// }
