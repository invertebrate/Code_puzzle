#include "game_manager.h"
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

class AIObject // an addon object to GameObject that has runtime functionality
{
	  public:
		GameObject *host;
		Vector2int patrol_path[2] = {{-1, -1}, {-1, -1}}; // figure out a good default value
		Vector2int current_target = {-1, -1};
		e_behaviour_type behaviour = e_behaviour_type_null;
		e_task_type task = e_task_type_null;
		AIObject(GameObject *host, e_behaviour_type type, Vector2int *path) : host(host)
		{
				behaviour = type;
				patrol_path[0] = path[0];
				patrol_path[1] = path[1];
				current_target = patrol_path[0];
		}
		~AIObject()
		{
		}
		void position_resolve() // moves the object according to its objective
		{
				if (behaviour == e_behaviour_type_patrol)
				{
						patrol_step_resolve();
				}
				if (behaviour == e_behaviour_type_follow)
				{
						follow_step_resolve();
				}
		}
		void follow_step_resolve()
		{
				Vector2int step;
				Vector2int distance;

				distance = host->game_manager_get()->player->coordinates_get() - host->coordinates_get();
				step = calculate_next_step(distance);
				host->move_to(step + host->coordinates_get());
		}
		void patrol_step_resolve()
		{
				Vector2int step;
				Vector2int distance;

				distance = current_target - host->coordinates_get();
				if (distance == Vector2int{0, 0})
				{
						if (current_target == patrol_path[0])
								current_target = patrol_path[1];
						else if (current_target == patrol_path[1])
								current_target = patrol_path[0];
						distance = current_target - host->coordinates_get();
				}
				step = calculate_next_step(distance);
				host->move_to(step + host->coordinates_get());
		}
		Vector2int calculate_next_step(Vector2int distance)
		{
				Vector2int step = {0, 0};
				if (abs(distance.x) > abs(distance.y) && distance.x != 0)
				{
						// move x
						step.x = distance.x / abs(distance.x);
						step.y = 0;
				}
				else if (distance.y != 0)
				{
						// move y
						step.y = distance.y / abs(distance.y);
						step.x = 0;
				}
				return (step);
		}
		void task_resolve()
		{
		}
};

// possible patterns:
// patrol
// follow
// go perform a task