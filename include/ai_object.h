#include "game_object.h"

enum e_behaviour_type
{
		e_behaviour_type_null = 20,
		e_behaviour_type_patrol = 21,
		e_behaviour_type_follow = 22,
		e_behaviour_type_task = 23
};
enum e_task_type
{
		e_task_type_null = 30,
		e_task_type_sabotage = 31
};
enum e_direction
{
		e_direction_ab = 1,
		e_direction_ba = -1
};

class AIObject // an addon object to GameObject that has runtime functionality
{
	  public:
		GameObject *host;
		Vector2int patrol_path[2] = {{-1, -1}, {-1, -1}}; // figure out a good default value
		Vector2int current_target = {-1, -1};
		int direction = e_direction_ab;
		e_behaviour_type behaviour = e_behaviour_type_null;
		e_task_type task = e_task_type_null;
		AIObject() // add parameters like in GameObject
		{
		}
		~AIObject()
		{
		}
		void position_resolve() // moves the object according to its objective
		{
				if (behaviour == e_behaviour_type_patrol)
				{
						Vector2int target_pos;
						Vector2int distance;

						if (direction == e_direction_ba)
						{
								if (host->coordinates_get() == patrol_path[0])
								{
										direction = e_direction_ab;
										patrol_step_ab_get(target_pos); // step in opposite  direction
								}
								else
										patrol_step_ba_get(target_pos); // continue as normal
						}
						else
						{
								if (host->coordinates_get() == patrol_path[1])
								{
										direction = e_direction_ba;
										patrol_step_ba_get(target_pos); // step in opposite  direction
								}
								else
										patrol_step_ab_get(target_pos); // continue as normal
						}
						if (!(target_pos == host->coordinates_get()))
								host->move_to(target_pos);
				}
		}
		void patrol_step_ab_get(Vector2int &target_pos)
		{
				Vector2int distance;

				distance.x = patrol_path[0].x - host->coordinates_get().x;
				distance.y = patrol_path[0].y - host->coordinates_get().y;
				if (abs(distance.x) > abs(distance.y))
				{
						target_pos.x = host->coordinates_get().x + distance.x / abs(distance.x);
						target_pos.y = host->coordinates_get().y;
						// move along x
				}
				else
				{
						target_pos.y = host->coordinates_get().y + distance.y / abs(distance.y);
						target_pos.x = host->coordinates_get().x;
						// move along y
				}
		}
		void patrol_step_ba_get(Vector2int &target_pos)
		{
				Vector2int distance;

				distance.x = patrol_path[1].x - host->coordinates_get().x;
				distance.y = patrol_path[1].y - host->coordinates_get().y;
				if (abs(distance.x) > abs(distance.y))
				{
						target_pos.x = host->coordinates_get().x + distance.x / abs(distance.x);
						target_pos.y = host->coordinates_get().y;
						// move along x
				}
				else
				{
						target_pos.y = host->coordinates_get().y + distance.y / abs(distance.y);
						target_pos.x = host->coordinates_get().x;
						// move along y
				}
		}
		void task_resolve()
		{
		}
};

// possible patterns:
// patrol
// follow
// go perform a task