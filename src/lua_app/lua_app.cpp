#include "lua_app.hpp"
#define S_WINDOW_SIZE_X "window_size_x"
#define S_WINDOW_SIZE_Y "window_size_y"
#define S_STEP_TIME "step_time"
#define S_FPS_CAP "fps_cap"

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

void commands_read(GameManager *manager, const char *file);
// function that reads the settings file and assigns the settings to game at init
// LUA COROUTINES! for something//
// LUA REGISTRY INDEX store
void settings_read(GameManager *manager, const char *file)
{
		lua_State *L = luaL_newstate();
		luaL_openlibs(L);
		int r = luaL_dofile(L, file);
		if ((r = check_lua(L, r)))
		{
				r = lua_getglobal(L, SETTINGS_FILE);
				if (lua_istable(L, -1))
				{
						settings_parse(manager, L);
				}
		}
		lua_close(L);
}

int fromlua_move_player(lua_State *L)
{
		int a = 0;
		int b = 0;
		GameManager *manager = NULL;
		if (lua_gettop(L) == 3)
		{
				manager = *((GameManager **)lua_topointer(L, 1));
				a = (int)lua_tonumber(L, 2);
				b = (int)lua_tonumber(L, 3);
		}
		else
		{
				lua_pushnumber(L, e_command_error_narguments);
				return (1);
		}
		manager->player->move_to(Vector2int{a, b});
		lua_pushnumber(L, e_command_log_success);

		return (1);
}

void commands_read(GameManager *manager, const char *file)
{
		lua_State *L = luaL_newstate();
		luaL_openlibs(L);
		lua_register(L, "inlua_move_player", fromlua_move_player);
		void *managerptr = lua_newuserdata(L, sizeof(GameManager *)); // allocates space in the stack
		*((GameManager **)managerptr) = manager;
		lua_setglobal(L, "manager");
		int r = luaL_dofile(L, file);
		if ((r = check_lua(L, r)))
		{
				// r = lua_getglobal(L, "commands");
				// if (lua_istable(L, -1))
				// {
				// 		settings_parse(manager, L);
				// }
				printf("commands read\n");
		}
		lua_close(L);
		(void)manager;
}