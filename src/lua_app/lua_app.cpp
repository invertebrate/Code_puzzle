#include "lua_app.hpp"
#define F_GRID_SIZE_X "grid_size_x"
#define F_GRID_SIZE_Y "grid_size_y"
#define F_WINDOW_SIZE_X "window_size_x"
#define F_WINDOW_SIZE_Y "window_size_y"
#define F_TIME_STEP "time_step"
#define F_FPS_CAP "fps_cap"

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

static int setting_get(lua_State *L, const char *s)
{
		lua_getglobal(L, s);
		if (lua_isnumber(L, -1))
		{
				return ((int)lua_tonumber(L, -1));
		}
		else
				return (0);
}

// function that reads the settings file and assigns the settings to game at init
void settings_parse(GameManager *manager, const char *file)
{
		lua_State *L = luaL_newstate();
		// luaL_openlibs(L);
		int grid_size;
		int r = luaL_dofile(L, file);
		if ((r = check_lua(L, r)))
		{
				manager->grid_size_set({setting_get(L, F_GRID_SIZE_X), setting_get(L, F_GRID_SIZE_X)});
				manager->window_size_set({setting_get(L, F_WINDOW_SIZE_X), setting_get(L, F_WINDOW_SIZE_X)});
				manager->step_time_set(setting_get(L, F_TIME_STEP));
				manager->fps_cap_set((float)setting_get(L, F_FPS_CAP));

				// grid_size = 10
				// window_size = 1000
				// time_step = 1.0
				// fps_cap = 60
		}
		printf("grid_size read from file: %d\n", grid_size);
		lua_close(L);
		(void)manager;
}