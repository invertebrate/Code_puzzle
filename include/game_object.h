#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "vector2.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class GameManager;
class AIObject;
enum e_object_type : unsigned int;

class GameObject
{
	  private:
		SDL_Texture *sdl_texture = NULL;
		SDL_Rect *sdl_rect = NULL;
		uint16_t render_layer;
		GameManager *game_manager = NULL;
		Vector2int size;
		Vector2 pos;
		float scale;
		bool passable;
		e_object_type type;
		Vector2int coordinates;

	  public:
		AIObject *ai_object = NULL;
		GameObject(GameManager *manager, const char *file, Vector2int dimensions, Vector2int pos);
		GameObject();
		~GameObject();
		static GameObject *hero_object_create(GameManager *manager, GameObject *obj);
		static GameObject *enemy_object_create(GameManager *manager, GameObject *obj);
		static GameObject *enemy_2_object_create(GameManager *manager, GameObject *obj);
		static GameObject *finish_object_create(GameManager *manager, GameObject *obj);
		bool bounds_check(Vector2int coordinates);
		void texture_set(SDL_Texture *texture);
		SDL_Texture *texture_get();
		SDL_Rect *sdl_rect_get();
		GameManager *game_manager_get();
		void render_layer_set(uint16_t layer);
		uint16_t render_layer_get();
		void move_to(Vector2int location);
		Vector2int coordinates_get();
		void size_set(Vector2int size);
		Vector2int size_get();
		void pos_set(Vector2 pos);
		Vector2 pos_get();
		float scale_get();
		void scale_set(float s);
		void passable_set(bool passable);
		bool is_passable();
		e_object_type type_get();
		void type_set(e_object_type t);
		void print();
		bool operator==(const GameObject &other);
};

#endif