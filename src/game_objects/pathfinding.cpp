#include "pathfinding.hpp"

int get_index(t_pf_data *data, int x, int y)
{
		return (y * (data->width) + x);
}
void get_coords(t_pf_data *data, uint32_t index, uint32_t *coords)
{
		coords[0] = index % (data->width);
		coords[1] = index / (data->width);
}

void create_start(t_pf_data *data, uint32_t sizex, t_upair &start)
{
		auto index = rand() % sizex;
		uint32_t coords[2];
		get_coords(data, index, coords);
		start.first = coords[0];
		start.second = coords[1];
		data->map[index] = PF_VALUE_START;
}
void create_finish(t_pf_data *data, uint32_t offset, uint32_t sizex)
{
		uint32_t index = rand() % sizex + offset;
		data->map[index] = PF_VALUE_FINISH;
}

size_t find_smallest(t_pf_data *data, t_upair *coordinates, size_t size)
{
		std::vector<uint32_t> values;
		for (uint32_t i = 0; i < size; i++)
		{
				values.push_back(data->map[get_index(data, coordinates[i].first, coordinates[i].second)]);
		}
		return (std::min_element(values.begin(), values.end()) - values.begin());
}

uint32_t get_arr(t_pf_data *data, t_upair a, t_upair b, t_upair c, t_upair d, t_upair *arr)
{
		uint32_t size = 0;
		if (a.first < data->width && a.second < data->height)
		{
				arr[size] = a;
				size++;
		}
		if (b.first < data->width && b.second < data->height)
		{
				arr[size] = b;
				size++;
		}
		if (c.first < data->width && c.second < data->height)
		{
				arr[size] = c;
				size++;
		}
		if (d.first < data->width && d.second < data->height)
		{
				arr[size] = d;
				size++;
		}
		return (size);
}

t_upair find_smallest_neighbour(t_pf_data *data, t_upair coords)
{
		t_upair right = (t_upair){coords.first + 1, coords.second};
		t_upair top = (t_upair){coords.first, coords.second - 1};
		t_upair left = (t_upair){coords.first - 1, coords.second};
		t_upair down = (t_upair){coords.first, coords.second + 1};
		t_upair arr[4];
		uint32_t arr_size = get_arr(data, right, top, left, down, arr);
		size_t index = find_smallest(data, arr, arr_size);
		// printf("smallest x %u y %u value: %u\n", arr[index].first,
		// arr[index].second,
		//        map[get_index(arr[index].first, arr[index].second)]);
		return (arr[index]);
}

void trace_path(t_pf_data *data, t_upair end_coords)
{
		t_upair coords = end_coords;
		data->path->push_front(end_coords);
		while (true)
		{
				if (data->map[get_index(data, coords.first, coords.second)] == PF_VALUE_START)
						break;
				coords = find_smallest_neighbour(data, coords);
				data->path->push_front(coords);
		}
		printf("route size i.e. step amount: %lu\n", data->path->size());
}

uint32_t update_node(t_pf_data *data, uint32_t x, uint32_t y, int32_t current_weight)
{
		static uint32_t queue_total = 0;
		uint32_t index = 0;
		if (x >= data->width || y >= data->height)
		{ // out of bounds
				return (0);
		}
		index = get_index(data, x, y);
		if (data->map[index] == PF_VALUE_OBSTACLE)
		{
				return (0);
		}
		if (data->map[index] == PF_VALUE_FINISH)
		{ // found finish
				data->path->push_front(t_upair(x, y));
				return (2);
		}
		if (data->node_states[index] & e_node_visited)
		{
				return (0);
		}
		if (data->map[index] > current_weight && ((data->node_states[index] & e_node_visited) != e_node_visited))
		{
				data->map[index] = current_weight + 1;
				if ((data->node_states[index] & e_node_queued) != e_node_queued)
				{
						queue_total++;
						data->queue->push_back(t_upair(x, y));
						data->node_states[index] |= e_node_queued;
						return (1);
				}
		}
		// if (queue_total % 100 == 0)
		// printf("queue total: %u\n", queue_total);
		return (0);
}

void print_map(uint32_t *map);

uint32_t maximum(uint32_t a, uint32_t b)
{
		return (a > b ? a : b);
}

uint32_t update_neighbors(t_pf_data *data, t_upair node)
{
		uint32_t r = 0;
		uint32_t x = node.first;
		uint32_t y = node.second;
		uint32_t current_index = get_index(data, x, y);
		int32_t current_weight = data->map[current_index];
		data->node_states[current_index] |= e_node_visited;
		r = maximum(update_node(data, x + 1, y, current_weight), r);
		r = maximum(update_node(data, x, y - 1, current_weight), r);
		r = maximum(update_node(data, x - 1, y, current_weight), r);
		r = maximum(update_node(data, x, y + 1, current_weight), r);
		if (r == 2)
		{
				printf("found finish\n");
				trace_path(data, (t_upair){x, y});
				for (auto it = data->path->begin(); it != data->path->end(); it++)
				{
						if (data->map[get_index(data, (*it).first, (*it).second)] != PF_VALUE_FINISH &&
							data->map[get_index(data, (*it).first, (*it).second)] != PF_VALUE_START)
								data->map[get_index(data, (*it).first, (*it).second)] = PF_VALUE_PATH;
				}
		}
		return (r);
}

uint32_t *create_map(t_pf_data *data)
{
		uint32_t i = 0;
		uint32_t j = 0;
		uint32_t *map;

		map = (uint32_t *)malloc(sizeof(uint32_t) * data->width * data->height);
		while (i < data->height)
		{
				while (j < data->width)
				{
						map[i * (data->width) + j] = PF_VALUE_EMPTY;
						if (rand() % 100 < PF_VALUE_OBSTACLE_DENSITY)
						{
								map[i * (data->height) + j] = PF_VALUE_OBSTACLE;
						}
						j++;
				}
				if (i == PF_VALUE_START)
						create_start(data, data->width, data->start);
				if (i == data->height - 1)
						create_finish(data, (data->height - 1) * (data->width), data->height);
				i++;
				j = 0;
		}
		return (map);
}

void path_solve(t_pf_data *data)
{
		static uint32_t queue_max = 0;
		static uint32_t queue_bottom = 0;
		data->queue->push_back(data->start);
		printf("start: %u %u \n", data->start.first, data->start.second);
		while (data->queue->size() > 0)
		{
				auto first_in_queue = data->queue->front();
				auto last_in_queue = data->queue->back();
				if (data->map[get_index(data, last_in_queue.first, last_in_queue.second)] == PF_VALUE_FINISH &&
					queue_bottom == 0)
				{
						queue_bottom = queue_max;
						break;
				}
				if (update_neighbors(data, first_in_queue) == 2)
				{
						break;
				}
				if (data->queue->size() > queue_max)
						queue_max = data->queue->size();
				data->node_states[(uint32_t)get_index(data, first_in_queue.first, first_in_queue.second)] &=
					~e_node_queued;
				data->queue->pop_front();
				(void)last_in_queue;
		}
		(void)queue_bottom;
		printf("queue max: %u\n", queue_max);
}

uint8_t *node_states_init(uint32_t sizex, uint32_t sizey)
{
		uint8_t *node_states;
		node_states = (uint8_t *)malloc(sizeof(uint8_t) * sizex * sizey);
		memset(node_states, 0, sizex * sizey);
		return (node_states);
}

void print_map(t_pf_data *data)
{
		std::string str;
		std::string map_string;
		for (uint32_t i = 0; i < data->height * data->width; i++)
		{
				if (i > 0 && i % (data->width) == 0)
				{
						map_string.append("\n");
						str = std::to_string(data->map[i]);
						str.append("\t");
						map_string.append(str);
						str.append("\t");
				}
				else
				{
						str = std::to_string(data->map[i]);
						str.append("\t");
						map_string.append(str);
				}
		}
		printf("%s\n", map_string.c_str());
}

void path_find(int32_t *map, t_upair start, uint32_t width, uint32_t height,
			   t_path *path) // path should contain both the target and start points
{
		srand(time(NULL));

		t_pf_data data;
		data.queue = new t_queue();
		data.map = map;
		data.width = width;
		data.height = height;
		data.path = path;
		data.start = start;
		// create_map(&data);
		data.node_states = node_states_init(width, height);
		printf("finding path: w %u, h %u\n", width, height);
		print_map(&data);
		printf("\n==============================================\n\n");
		path_solve(&data);
		printf("\nRESULT:==============================\n\n");
		print_map(&data);
}
