#include "ai_object.hpp"

void ai_check_for_obstacles(GameObject *object, void *param, void *res)
{
		// create a generalist object/obstacle type finder functions that can be input here
		// if object.type == object type obstacle -> return PF_VALUE_OBSTACLE else return (PF_VALUE_MAX)
		if (object->is_solid())
		{
				*((uint32_t *)res) = PF_VALUE_OBSTACLE;
				printf("found obstacle at %u %u res is %u\n", object->coordinates_get().x, object->coordinates_get().y,
					   *((uint32_t *)res));
				return;
		}
		(void)param;
}

uint32_t *ai_map_create(GameGrid *game_grid, Vector2int start, Vector2int target)
{
		uint32_t *map;
		uint32_t temp_res = PF_VALUE_EMPTY;
		uint32_t width = game_grid->grid_width_get();
		uint32_t height = game_grid->grid_height_get();
		t_grid *grid = game_grid->grid_get();

		map = (uint32_t *)malloc(sizeof(uint32_t) * width * height);
		for (uint32_t i = 0; i < width * height; i++)
		{
				map[i] = PF_VALUE_EMPTY;
				game_grid->operate_on_objects_at(ai_check_for_obstacles, game_grid->grid_coords_get(i), NULL,
												 &temp_res);
				if (temp_res == PF_VALUE_OBSTACLE)
				{
						printf("res was obstacle: %u \n", temp_res);
						map[i] = PF_VALUE_OBSTACLE;
				}
				temp_res = PF_VALUE_EMPTY;
		}
		map[game_grid->grid_index_get(start)] = PF_VALUE_START;
		map[game_grid->grid_index_get(target)] = PF_VALUE_FINISH;
		(void)grid;
		return (map);
}

void ai_find_path_to_target(GameGrid *game_grid, t_upair start, t_upair target, t_path *path)
{
		uint32_t *map = NULL;
		uint32_t width = game_grid->grid_width_get();
		uint32_t height = game_grid->grid_height_get();

		map = ai_map_create(game_grid, Vector2int(start.first, start.second), Vector2int(target.first, target.second));
		path_find(map, width, height, path);
}