#ifndef GRID_H
#define GRID_H

#include "game_object.h"
#include <map>
#include <stdint.h>
#include <stdio.h>
#include <vector>

// gameobjects should know where they are on the grid and grid should know what objects are on each slot
class GameGrid
{
	  private:
		uint32_t width = 10;
		uint32_t height = 10;
		std::map<uint32_t, std::vector<GameObject *> *> grid;
		SDL_Texture *sdl_texture;

	  public:
		GameGrid()
		{

				for (uint32_t h = 0; h < height; h++)
				{
						for (uint32_t w = 0; w < width; w++)
						{
								std::vector<GameObject *> *object_list =
									new std::vector<GameObject *>(); // kinda sus syntax bc of pointer
								auto pair = std::make_pair(w + h * w, object_list);
								grid.insert(pair); // hopefully this makes a map with coordinates as keys and an object
												   // vector as value
												   // test gameobject insertion and indexing works
						}
				}
		}
		~GameGrid();
		std::map<uint32_t, std::vector<GameObject *> *> *grid_get()
		{
				return (&grid);
		}
		void texture_set(SDL_Texture *texture)
		{
				sdl_texture = texture;
		}
		SDL_Texture *texture_get()
		{
				return (sdl_texture);
		}
};

#endif