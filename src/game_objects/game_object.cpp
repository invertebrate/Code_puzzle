#include "game_object.h"
#include "game_manager.h"

GameObject::GameObject(GameManager *manager, const char *file, Vector2 dimensions, Vector2 pos)
	: size(dimensions), pos(pos)
{
		sdl_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
		sdl_rect->h = dimensions.x;
		sdl_rect->w = dimensions.y;
		sdl_rect->x = pos.x;
		sdl_rect->y = pos.y;
		scale = 1.0;
		sdl_texture = manager->game_renderer_get()->texture_create(file); // NON RUNTIME TEXTURE LOADING!
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