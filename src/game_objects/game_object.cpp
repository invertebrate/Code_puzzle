#include "game_object.h"
#include "code_puzzle.h"
#include "game_manager.h"

GameObject::GameObject(GameManager *manager, const char *file, Vector2int dimensions, Vector2int coords)
	: size(dimensions), coordinates(coords)
{
		game_manager = manager;
		printf("creating a gameobject with dimensions %d, %d: \n", dimensions.x, dimensions.y);
		sdl_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
		sdl_rect->h = (int)dimensions.x;
		sdl_rect->w = (int)dimensions.y;
		printf("line width %f: \n", manager->game_grid_get()->line_width_get());
		sdl_rect->x = coords.x * (GRID_SQR_SIZE + game_manager->game_grid_get()->line_width_get()) *
					  ((float)WINDOW_SIZE / GRID_WIDTH);
		sdl_rect->y = coords.y * (GRID_SQR_SIZE + game_manager->game_grid_get()->line_width_get()) *
					  ((float)WINDOW_SIZE / GRID_WIDTH);
		scale = 1.0;
		sdl_texture = manager->asset_textures[file];
		bounds_check(coords);

		// add gameobject position in pixels from location info
}
GameObject::~GameObject()
{
}
GameObject *GameObject::hero_object_create(GameManager *manager, GameObject *obj)
{
		obj = new GameObject(manager, HERO_TEXTURE,
							 Vector2int((float)GRID_SQR_SIZE * ((float)WINDOW_SIZE / GRID_WIDTH),
										(float)GRID_SQR_SIZE * ((float)WINDOW_SIZE / GRID_HEIGHT)),
							 Vector2int(0, 0));
		obj->type_set(e_object_type_hero);
		manager->game_objects.push_back(obj);
		return (obj);
}
GameObject *GameObject::enemy_object_create(GameManager *manager, GameObject *obj)
{
		obj = new GameObject(manager, ENEMY_TEXTURE,
							 Vector2int((float)GRID_SQR_SIZE * ((float)WINDOW_SIZE / GRID_WIDTH),
										(float)GRID_SQR_SIZE * ((float)WINDOW_SIZE / GRID_HEIGHT)),
							 Vector2int(0, 0));
		obj->type_set(e_object_type_enemy);
		manager->game_objects.push_back(obj);
		return (obj);
}
GameObject *GameObject::enemy_2_object_create(GameManager *manager, GameObject *obj)
{
		obj = new GameObject(manager, ENEMY_TEXTURE,
							 Vector2int((float)GRID_SQR_SIZE * ((float)WINDOW_SIZE / GRID_WIDTH),
										(float)GRID_SQR_SIZE * ((float)WINDOW_SIZE / GRID_HEIGHT)),
							 Vector2int(0, 0));
		obj->type_set(e_object_type_enemy_2);
		manager->game_objects.push_back(obj);
		return (obj);
}
GameObject *GameObject::finish_object_create(GameManager *manager, GameObject *obj)
{
		obj = new GameObject(manager, FINISH_TEXTURE,
							 Vector2int((float)GRID_SQR_SIZE * ((float)WINDOW_SIZE / GRID_WIDTH),
										(float)GRID_SQR_SIZE * ((float)WINDOW_SIZE / GRID_HEIGHT)),
							 Vector2int(0, 0));
		obj->type_set(e_object_type_finish);
		manager->game_objects.push_back(obj);
		return (obj);
}
bool GameObject::bounds_check(Vector2int coordinates)
{
		if (coordinates.x > game_manager_get()->game_grid_get()->grid_width_get() - 1 || coordinates.x < 0 ||
			coordinates.y > game_manager_get()->game_grid_get()->grid_height_get() - 1 || coordinates.y < 0)
		{
				printf("WARNING: Attempted to place gameobject outside of bounds in coordinates: x: %d, y: %d\n",
					   coordinates.x, coordinates.y);
				return (false);
		}
		else
				return (true);
}

void GameObject::texture_set(SDL_Texture *texture)
{
		sdl_texture = texture;
}
SDL_Texture *GameObject::texture_get()
{
		return (sdl_texture);
}
SDL_Rect *GameObject::sdl_rect_get()
{
		return (sdl_rect);
}

GameManager *GameObject::game_manager_get()
{
		return (game_manager);
}
void GameObject::render_layer_set(uint16_t layer)
{
		(void)layer;
}
uint16_t GameObject::render_layer_get()
{
		return (render_layer);
}
void GameObject::move_to(Vector2int coords)
{
		if (bounds_check(coords))
		{
				game_manager->game_grid_get()->remove_object_at(this, this->coordinates_get());
				sdl_rect->x = coords.x * (GRID_SQR_SIZE + game_manager->game_grid_get()->line_width_get()) *
							  ((float)WINDOW_SIZE / GRID_WIDTH);
				sdl_rect->y = coords.y * (GRID_SQR_SIZE + game_manager->game_grid_get()->line_width_get()) *
							  ((float)WINDOW_SIZE / GRID_WIDTH);
				coordinates.x = coords.x;
				coordinates.y = coords.y;
				game_manager->game_grid_get()->add_object_at(this, coords);
		}
}
Vector2int GameObject::coordinates_get()
{
		return (coordinates);
}
void GameObject::size_set(Vector2int s)
{
		size = s;
}
Vector2int GameObject::size_get()
{
		return (size);
}
void GameObject::pos_set(Vector2 position)
{
		pos = position;
}
Vector2 GameObject::pos_get()
{
		return (pos);
}
float GameObject::scale_get()
{
		return (scale);
}
void GameObject::scale_set(float s)
{
		scale = s;
}
void GameObject::passable_set(bool pass)
{
		passable = pass;
}
bool GameObject::is_passable()
{
		return (passable);
}
int GameObject::type_get()
{
		return (type);
}
void GameObject::type_set(int t)
{
		type = t;
}
void type_set(int t);
void GameObject::print()
{
		printf("-----------------\n"
			   "GameObject: %p\n"
			   "game_manager: %p\n"
			   "sdl_texture: %p\n"
			   "render_layer: %u\n"
			   "sdl_rect: %p | x: %d | y: %d | w: %d | h: %d\n"
			   "size: w: %d, h: %d\n"
			   "coordinates: x: %d, y: %d\n"
			   "position: x: %f | y: %f\n"
			   "-----------------\n",
			   this, game_manager, sdl_texture, render_layer, sdl_rect, sdl_rect->x, sdl_rect->y, sdl_rect->w,
			   sdl_rect->h, size.x, size.y, coordinates.x, coordinates.y, pos.x, pos.y);
}
// bool GameObject::operator==(const GameObject &other)
// {
// 		if (this == other)
// 				return (true);
// 		else
// 				return (false)
// }