#include "game_object.h"
#include "game_manager.h"

GameObject::GameObject(const char *file, float size, Vector2 pos) : size(size), pos(pos)
{
		sdl_texture = game_manager->renderer_get()->texture_create(file);
}
GameObject::GameObject()
{
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
float GameObject::size_get()
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
void GameObject::passable_set(bool pass)
{
		passable = pass;
}
bool GameObject::is_passable()
{
		return (passable);
}