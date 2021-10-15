#include "game_object.h"
#include "game_manager.h"

GameObject::GameObject(GameManager *manager, const char *file, Vector2 dimensions, Vector2 pos)
	: size(dimensions), pos(pos)
{
		printf("creating a gameobject with dimensions %f, %f: \n", dimensions.x, dimensions.y);
		sdl_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
		sdl_rect->h = (int)dimensions.x;
		sdl_rect->w = (int)dimensions.y;
		sdl_rect->x = pos.x;
		sdl_rect->y = pos.y;
		scale = 1.0;
		sdl_texture = manager->asset_textures[file]; // NON RUNTIME TEXTURE LOADING!
}
GameObject::~GameObject()
{
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
void GameObject::move_to(Vector2 location)
{
		(void)location;
}
void GameObject::size_set(float size)
{
		size = size;
}
Vector2 GameObject::size_get()
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
SDL_Texture *sdl_texture;
SDL_Rect *sdl_rect;
uint16_t render_layer;
GameManager *game_manager;
Vector2 size;
Vector2 pos;
float scale;
bool passable;
void GameObject::print()
{
		printf("-----------------\n"
			   "GameObject:\n"
			   "game_manager: %p\n"
			   "sdl_texture: %p\n"
			   "render_layer: %u\n"
			   "sdl_rect: %p | x: %d | y: %d | w: %d | h: %d\n"
			   "size: w: %f, h: %f\n"
			   "position: x: %f | y: %f\n"
			   "-----------------\n",
			   game_manager, sdl_texture, render_layer, sdl_rect, sdl_rect->x, sdl_rect->y, sdl_rect->w, sdl_rect->h,
			   size.x, size.y, pos.x, pos.y);
}