#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "code_puzzle.h"

class GameObject {
      private:
	SDL_Texture *texture;

      public:
	Vector2 pos;
	GameObject();
	~GameObject();
	void move_to(Vector2 position);
}

#endif