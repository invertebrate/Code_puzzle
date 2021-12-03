#include "lua_app.hpp"
#define S_WINDOW_SIZE_X "window_size_x"
#define S_WINDOW_SIZE_Y "window_size_y"
#define S_STEP_TIME "step_time"
#define S_FPS_CAP "fps_cap"
#define S_SETTINGS "settings"

static int check_lua(lua_State *L, int r)
{
		if (r == LUA_OK)
		{
				return (1);
		}
		else
		{
				printf("ERROR LUA: %s", lua_tostring(L, -1));
				return (0);
		}
		return (0);
}

static void settings_window_size_get(GameManager *manager, lua_State *L)
{
		Vector2int size = {0, 0};
		lua_pushstring(L, S_WINDOW_SIZE_X);
		lua_gettable(L, -2);
		if (lua_isnumber(L, -1))
		{
				size.x = (int)lua_tonumber(L, -1);
		}
		lua_pop(L, 1);

		lua_pushstring(L, S_WINDOW_SIZE_Y);
		lua_gettable(L, -2);
		if (lua_isnumber(L, -1))
		{
				size.y = (int)lua_tonumber(L, -1);
		}
		lua_pop(L, 1);

		if (size >= Vector2int{1, 1})
		{
				manager->window_size_set(size);
		}
}
static void settings_fps_cap_get(GameManager *manager, lua_State *L)
{

		lua_pushstring(L, S_FPS_CAP);
		lua_gettable(L, -2);
		if (lua_isnumber(L, -1))
		{
				manager->fps_cap_set((int)lua_tonumber(L, -1));
		}
		lua_pop(L, 1);
}
static void settings_step_time_get(GameManager *manager, lua_State *L)
{

		lua_pushstring(L, S_STEP_TIME);
		lua_gettable(L, -2);
		if (lua_isnumber(L, -1))
		{
				manager->step_time_set((float)lua_tonumber(L, -1));
				printf("step time read: %f\n", (float)lua_tonumber(L, -1));
				lua_pop(L, 1);
		}
		lua_pop(L, 1);
}
static void settings_parse(GameManager *manager, lua_State *L)
{
		settings_window_size_get(manager, L);
		settings_fps_cap_get(manager, L);
		settings_step_time_get(manager, L);
}

void settings_read(GameManager *manager, const char *file)
{
		lua_State *L = luaL_newstate();
		luaL_openlibs(L);
		int r = luaL_dofile(L, file);

		if ((r = check_lua(L, r)))
		{
				r = lua_getglobal(L, S_SETTINGS);
				if (lua_istable(L, -1))
				{
						settings_parse(manager, L);
				}
		}
		lua_close(L);
}

int fromlua_move_player(lua_State *L)
{
		int x = 0;
		int y = 0;
		GameManager *manager = NULL;
		GameObject *player = NULL;
		if (lua_gettop(L) == 3)
		{
				manager = *((GameManager **)lua_topointer(L, 1));
				player = manager->player;
				x = (int)lua_tonumber(L, 2);
				y = (int)lua_tonumber(L, 3);
		}
		else
		{
				lua_pushnumber(L, e_command_error_narguments);
				return (1);
		}
		player->move_to(Vector2int{player->coordinates_get().x + x, player->coordinates_get().y + y});
		lua_pushnumber(L, e_command_log_success);
		return (1);
}

void commands_init(GameManager *manager, const char *file)
{
		lua_State *L = luaL_newstate();
		manager->lua_instance_set(L);
		luaL_openlibs(L);
		lua_register(L, "inlua_move_player", fromlua_move_player);
		void *managerptr = lua_newuserdata(L, sizeof(GameManager *));
		*((GameManager **)managerptr) = manager;
		lua_setglobal(L, "manager");
		int r = luaL_dofile(L, file);
		// manager->command_string
		std::ifstream command_stream("commands.lua");
		if (command_stream)
		{
				std::ostringstream ss;
				ss << command_stream.rdbuf();
				std::string *temp = new std::string(ss.str());
				manager->command_string_set(temp);
		}
		if ((r = check_lua(L, r)))
		{
				printf("commands initialized\n");
		}
}

void execute_command_line(GameManager *manager, int line_nb)
{
		std::string line;
		int i = 0;
		std::istringstream iss(*(manager->command_string_get()));

		while (std::getline(iss, line)) // test memory leaks
		{
				if (line_nb == i)
						break;
				else
						i++;
		}
		int r = luaL_dostring(manager->lua_instance_get(), line.c_str());
		if ((r = check_lua(manager->lua_instance_get(), r)))
		{
				printf("command line number %d read successfully: %s", line_nb, line.c_str());
		}
} // called every time step