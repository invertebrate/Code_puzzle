#include "game_object.hpp"
#include "code_puzzle.hpp"

GameObject::GameObject(GameManager *manager, const char *file, Vector2int dimensions, Vector2int coords)
	: size(dimensions), coordinates(coords)
{
		game_manager = manager;
		GameGrid *grid = manager->game_grid_get();
		sdl_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
		sdl_rect->w = (int)dimensions.x;
		sdl_rect->h = (int)dimensions.y;
		sdl_rect->x = coords.x * (grid->grid_cell_size_get() + game_manager->game_grid_get()->line_width_get()) *
					  ((float)manager->window_size_get().x / grid->img_width_get());
		sdl_rect->y = coords.y * (grid->grid_cell_size_get() + game_manager->game_grid_get()->line_width_get()) *
					  ((float)manager->window_size_get().y / grid->img_height_get());
		scale = 1.0;
		collision = false;
		solid = false;
		sdl_texture = manager->asset_textures[file];
}
GameObject::~GameObject()
{
		free(sdl_rect);
}
GameObject *GameObject::hero_object_create(GameManager *manager, GameObject *obj)
{
		uint32_t window_x = manager->window_size_get().x;
		uint32_t window_y = manager->window_size_get().y;
		uint32_t grid_x = manager->game_grid_get()->img_width_get();
		uint32_t grid_y = manager->game_grid_get()->img_height_get();
		uint32_t sqr_size = manager->game_grid_get()->grid_cell_size_get();
		obj = new GameObject(
			manager, HERO_TEXTURE,
			Vector2int((float)sqr_size * ((float)window_x / grid_x), (float)sqr_size * ((float)window_y / grid_y)),
			Vector2int(0, 0));
		obj->collision = true;
		obj->solid = false;
		obj->type_set(e_object_type_hero);
		manager->game_objects.push_back(obj);
		return (obj);
}
GameObject *GameObject::enemy_object_create(GameManager *manager, GameObject *obj)
{
		uint32_t window_x = manager->window_size_get().x;
		uint32_t window_y = manager->window_size_get().y;
		uint32_t grid_x = manager->game_grid_get()->img_width_get();
		uint32_t grid_y = manager->game_grid_get()->img_height_get();
		uint32_t sqr_size = manager->game_grid_get()->grid_cell_size_get();
		obj = new GameObject(
			manager, ENEMY_TEXTURE,
			Vector2int((float)sqr_size * ((float)window_x / grid_x), (float)sqr_size * ((float)window_y / grid_y)),
			Vector2int(0, 0));
		obj->collision = true;
		obj->solid = false;
		obj->type_set(e_object_type_enemy);
		manager->game_objects.push_back(obj);
		return (obj);
}
GameObject *GameObject::enemy_2_object_create(GameManager *manager, GameObject *obj)
{
		uint32_t window_x = manager->window_size_get().x;
		uint32_t window_y = manager->window_size_get().y;
		uint32_t grid_x = manager->game_grid_get()->img_width_get();
		uint32_t grid_y = manager->game_grid_get()->img_height_get();
		uint32_t sqr_size = manager->game_grid_get()->grid_cell_size_get();
		obj = new GameObject(
			manager, ENEMY_TEXTURE,
			Vector2int((float)sqr_size * ((float)window_x / grid_x), (float)sqr_size * ((float)window_y / grid_y)),
			Vector2int(0, 0));
		obj->collision = true;
		obj->solid = false;
		obj->type_set(e_object_type_enemy_2);
		manager->game_objects.push_back(obj);
		return (obj);
}
GameObject *GameObject::obstacle_1_object_create(GameManager *manager, GameObject *obj)
{
		uint32_t window_x = manager->window_size_get().x;
		uint32_t window_y = manager->window_size_get().y;
		uint32_t grid_x = manager->game_grid_get()->img_width_get();
		uint32_t grid_y = manager->game_grid_get()->img_height_get();
		uint32_t sqr_size = manager->game_grid_get()->grid_cell_size_get();
		obj = new GameObject(
			manager, OBSTACLE_TEXTURE,
			Vector2int((float)sqr_size * ((float)window_x / grid_x), (float)sqr_size * ((float)window_y / grid_y)),
			Vector2int(0, 0));
		obj->collision = true;
		obj->solid = true;
		obj->type_set(e_object_type_obstacle_1);
		manager->game_objects.push_back(obj);
		return (obj);
}
GameObject *GameObject::finish_object_create(GameManager *manager, GameObject *obj)
{
		uint32_t window_x = manager->window_size_get().x;
		uint32_t window_y = manager->window_size_get().y;
		uint32_t grid_x = manager->game_grid_get()->img_width_get();
		uint32_t grid_y = manager->game_grid_get()->img_height_get();
		uint32_t sqr_size = manager->game_grid_get()->grid_cell_size_get();
		obj = new GameObject(
			manager, FINISH_TEXTURE,
			Vector2int((float)sqr_size * ((float)window_x / grid_x), (float)sqr_size * ((float)window_y / grid_y)),
			Vector2int(0, 0));
		obj->collision = true;
		obj->solid = false;
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
void GameObject::has_solid_collider(GameObject *object, void *param, void *res)
{
		if (object->is_solid())
		{
				*((bool *)res) = true;
				// printf("was solid\n");
		}
		else
		{
				*((bool *)res) = false;
				// printf("was not solid\n");
		}
		(void)param;
}
bool GameObject::solid_collision_check(Vector2int coordinates)
{
		bool is_solid = false;
		GameGrid *grid = this->game_manager_get()->game_grid_get();
		grid->operate_on_objects_at(has_solid_collider, coordinates, NULL, &is_solid);
		(void)coordinates;
		(void)grid;
		return (is_solid);
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
		if (bounds_check(coords) && !(this->solid_collision_check(coords)))
		{
				GameManager *manager = this->game_manager_get();
				GameGrid *grid = manager->game_grid_get();
				uint32_t grid_x = grid->img_width_get();
				uint32_t grid_y = grid->img_height_get();
				uint32_t cell_size = grid->grid_cell_size_get();
				uint32_t window_x = manager->window_size_get().x;
				uint32_t window_y = manager->window_size_get().y;
				{
						game_manager->game_grid_get()->remove_object_at(this, this->coordinates_get());
						sdl_rect->x = coords.x * (cell_size + game_manager->game_grid_get()->line_width_get()) *
									  ((float)window_x / grid_x);
						sdl_rect->y = coords.y * (cell_size + game_manager->game_grid_get()->line_width_get()) *
									  ((float)window_y / grid_y);
						coordinates.x = coords.x;
						coordinates.y = coords.y;
						game_manager->game_grid_get()->add_object_at(this, coords);
				}
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
void GameObject::collision_set(bool collision)
{
		this->collision = collision;
}
bool GameObject::is_collision()
{
		return (this->collision);
}
bool GameObject::is_solid()
{
		return (this->solid);
}
e_object_type GameObject::type_get()
{
		return (type);
}
void GameObject::type_set(e_object_type t)
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
