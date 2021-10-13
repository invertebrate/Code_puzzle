#ifndef GRID_H
#define GRID_H

#include "game_object.h"
#include <map>
#include <stdint.h>
#include <stdio.h>
#include <vector>
typedef std::pair<uint32_t, uint32_t> t_coord_pair;

// gameobjects should know where they are on the grid and grid should know what objects are on each slot
class Grid
{
	  private:
		uint32_t width = 20;
		uint32_t height = 20;
		std::map<t_coord_pair, std::vector<GameObject *> *> grid;

	  public:
		// Grid();
		Grid()
		{
				for (uint32_t h = 0; h < height; h++)
				{
						for (uint32_t w = 0; w < width; w++)
						{
								std::vector<GameObject *> *object_list =
									new std::vector<GameObject *>(); // kinda sus syntax bc of pointer
								t_coord_pair coord = std::make_pair(w, h);
								auto pair = std::make_pair(coord, object_list);
								grid.insert(pair); // hopefully this makes a map with coordinates as keys and an object
												   // vector as value
												   // test gameobject insertion and indexing works
						}
				}
		}
		~Grid();
};

#endif