#include "lua_app.h"

// function that reads the settings file and assigns the settings to game at init
void settings_parse(GameManager *manager, const char *file)
{
		lua_State *L = luaL_newstate();
		int grid_size;
		int r = luaL_dofile(L, file);
		if (r == LUA_OK)
		{
				lua_getglobal(L, "grid_size");
				if (lua_isnumber(L, -1))
				{
						grid_size = (int)lua_tonumber(L, -1);
				}
		}
		else
		{
				printf("ERROR LUA: %s", lua_tostring(L, -1));
		}
		printf("grid_size read from file: %d\n", grid_size);
		lua_close(L);
		(void)manager;
}