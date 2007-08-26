/**
* @file lualove.h
* @author Anders Ruud
* @date 2006-11-24
* @brief A set of global aux. lua functions.
**/

#ifndef LOVE_LUALOVE_H
#define LOVE_LUALOVE_H

// LOVE
#include "Core.h"
#include "Scriptable.h"

// STL
#include <string>
using std::string;

// Boost

// Lua

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include "lua_glue.h"

namespace love
{

	class AbstractFile;

	void lualove_init(lua_State * L);
	void lualove_close(lua_State * L);

	bool lualove_loaddir(lua_State * L, const string & path);
	bool lualove_load(lua_State * L, AbstractFile * file);
	bool lualove_load(lua_State * L, const string & filename);

	bool lualove_is_function(lua_State * L, const string & tablename, const string & functionname);
	bool lualove_is_function(lua_State * L, const string & functionname);

	void lualove_check_functions(lua_State * L, Scriptable * scriptable, int mask = 0);

	void lualove_check_error(lua_State * L, int status, const string & info);

	void lualove_push_number(lua_State * L, lua_Number number);
	void lualove_push_global_number(lua_State * L, const string & name, lua_Number number);
	void lualove_push_pointer(lua_State * L, void * ptr, int type);
	void lualove_push_global_pointer(lua_State * L, void * ptr, const string & name, int type);

	void lualove_call_init(lua_State * L, void * ptr, const string & chunk, int type);


	void lualove_call_update(lua_State * L, void * ptr, const string & chunk, int type, float dt);
	void lualove_call_render(lua_State * L, void * ptr, const string & chunk, int type);

	void lualove_call_init_noarg(lua_State * L, Scriptable * scriptable);
	void lualove_call_update_noarg(lua_State *L, Scriptable * scriptable, float dt);
	void lualove_call_render_noarg(lua_State *L, Scriptable * scriptable);
	void lualove_call_keypressed_noarg(lua_State *L, Scriptable * scriptable, int key);
	void lualove_call_keyreleased_noarg(lua_State *L, Scriptable * scriptable, int key);
	void lualove_call_mousepressed_noarg(lua_State *L, Scriptable * scriptable, float x, float y, int state);
	void lualove_call_mousereleased_noarg(lua_State *L, Scriptable * scriptable, float x, float y, int state);

	void lualove_create_table(lua_State * L, const string & name);
	void lualove_push_chunk_number(lua_State * L, const string & name, lua_Number number);
	void lualove_push_all_globals(lua_State *L);




} // love

#endif

