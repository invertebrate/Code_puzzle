// This is a copyright notice regarding the lua binaries used in this project:

/******************************************************************************
 * Copyright (C) 1994-2020 Lua.org, PUC-Rio.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 ******************************************************************************/

#ifndef LUA_APP_H
#define LUA_APP_H
#include "lua.hpp"

#include "game_manager.hpp"
#include "game_object.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

#define F_COMMANDS_INIT_FILE "init.lua"
#define F_COMMANDS_FILE "commands.lua"
#define F_SETTINGS_FILE "settings.lua"

enum e_command_error
{
		e_command_error_narguments = -1
};
enum e_command_log
{
		e_command_log_success = 1000
};

void settings_read(GameManager *manager, const char *file);
void commands_init(GameManager *manager, const char *file);
void execute_command_line(GameManager *manager, int line_nb);

#endif