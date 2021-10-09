#include "code_puzzle.h"

// class GameObject
// {
// private:
// 	SDL_Texture	*sdl_texture;
// 	SDL_Rect	*sdl_rect;
// 	uint16_t	render_layer;
// public:
// 	Vector2		pos;
// 	float		size;
// 	bool		passable;
// 	GameObject(const *char file, float size, Vector2 pos);
// 	~GameObject();
// };

// GameObject::GameObject(const *char file, float size, Vector2 pos)
// 	: size(size), pos(pos)
// {
// 	sdl_texture = create_texture(renderer, file);
// }
// GameObject::~GameObject()
// {

// }
// GameObject::create_texture(SDL_Renderer *renderer, const char *file)
// {
// 	SDL_Texture *new_texture = NULL;
// 	SDL_Surface *loaded_surface = IMG_Load(file);
// 	if (loaded_surface == NULL)
// 		printf("unable to load the image %s! SDL_image Error: %s\n", file, IMG_GetError());
// 	else
// 	{
// 		new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
// 		if (new_texture == NULL)
// 			printf("unable to create the texture from %s! SDL Error: %s\n", file, SDL_GetError());
// 	}
// 	SDL_FreeSurface(loaded_surface);
// 	return (new_texture);
// }
// GameObject::move_to()
// {

// }
