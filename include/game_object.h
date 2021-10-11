#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "vector2.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class GameManager;

class GameObject
{
	  private:
		SDL_Texture *sdl_texture;
		SDL_Rect *sdl_rect;
		uint16_t render_layer;
		GameManager *game_manager;
		float size;
		Vector2 pos;
		bool passable;

	  public:
		GameObject(const char *file, float size, Vector2 pos);
		GameObject();
		~GameObject();
		void texture_set(SDL_Texture *texture);
		SDL_Texture *texture_get();
		GameManager *game_manager_get();
		void render_layer_set(uint16_t layer);
		uint16_t render_layer_get();
		void move_to(Vector2 location);
		void size_set(float size);
		float size_get();
		void pos_set(Vector2 pos);
		Vector2 pos_get();
		void passable_set(bool passable);
		bool is_passable();
};

#endif