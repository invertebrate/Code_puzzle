#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <map>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <unistd.h>
#include <vector>

#define PF_VALUE_OBSTACLE_DENSITY 25 // 0-100
#define PF_VALUE_START 0
#define PF_VALUE_OBSTACLE 99999
#define PF_VALUE_FINISH 88888
#define PF_VALUE_EMPTY 55555
#define PF_VALUE_PATH 777
#define PF_VALUE_MAX 0xFFFFFFFF

typedef std::pair<uint32_t, uint32_t> t_upair;
typedef std::deque<t_upair> t_queue;
typedef std::vector<t_upair> t_path;

enum e_node_status
{
		e_node_visited = 1 << 0,
		e_node_queued = 1 << 1
};

typedef struct s_pf_data
{
		uint32_t *map;
		uint32_t width;
		uint32_t height;
		t_upair start;
		t_upair finish;
		t_path *path;
		uint8_t *node_states;
		t_queue *queue;
} t_pf_data;

void path_find(uint32_t *map, uint32_t width, uint32_t height, t_path *path);

#endif