#include "LuaVM.h"

// LOVE
//#include "lualove_glue.h"

#include "Filesystem.h"

namespace love
{

	// Forward declaration.
	int lua_runtime_error(lua_State * L);
	std::string string_find_replace( std::string haystack, std::string needle, std::string replace);

	LuaVM::LuaVM()
	{
	}

	LuaVM::~LuaVM()
	{
	}

	lua_State * LuaVM::getL()
	{
		return L;
	}

	bool LuaVM::open()
	{
		L = lua_open();
		luaL_openlibs(L);

		// Overwrite load.
		luaL_dostring(L, "load = nil");

		// Create love constants.
		luaL_dostring(L, 
			"love = {"
			"key_unknown = 0,"
			"key_first = 0,"
			"key_backspace = 8,"
			"key_tab = 9,"
			"key_clear = 12,"
			"key_return = 13,"
			"key_pause = 19,"
			"key_escape = 27,"
			"key_space = 32,"
			"key_exclaim = 33,"
			"key_quotedbl = 34,"
			"key_hash = 35,"
			"key_dollar = 36,"
			"key_ampersand = 38,"
			"key_quote = 39,"
			"key_leftparen = 40,"
			"key_rightparen = 41,"
			"key_asterisk = 42,"
			"key_plus = 43,"
			"key_comma = 44,"
			"key_minus = 45,"
			"key_period = 46,"
			"key_slash = 47,"
			"key_0 = 48,"
			"key_1 = 49,"
			"key_2 = 50,"
			"key_3 = 51,"
			"key_4 = 52,"
			"key_5 = 53,"
			"key_6 = 54,"
			"key_7 = 55,"
			"key_8 = 56,"
			"key_9 = 57,"
			"key_colon = 58,"
			"key_semicolon = 59,"
			"key_less = 60,"
			"key_equals = 61,"
			"key_greater = 62,"
			"key_question = 63,"
			"key_at = 64,"

			"key_leftbracket = 91,"
			"key_backslash = 92,"
			"key_rightbracket = 93,"
			"key_caret = 94,"
			"key_underscore = 95,"
			"key_backquote = 96,"
			"key_a = 97,"
			"key_b = 98,"
			"key_c = 99,"
			"key_d = 100,"
			"key_e = 101,"
			"key_f = 102,"
			"key_g = 103,"
			"key_h = 104,"
			"key_i = 105,"
			"key_j = 106,"
			"key_k = 107,"
			"key_l = 108,"
			"key_m = 109,"
			"key_n = 110,"
			"key_o = 111,"
			"key_p = 112,"
			"key_q = 113,"
			"key_r = 114,"
			"key_s = 115,"
			"key_t = 116,"
			"key_u = 117,"
			"key_v = 118,"
			"key_w = 119,"
			"key_x = 120,"
			"key_y = 121,"
			"key_z = 122,"
			"key_delete = 127,"

			"key_kp0 = 256,"
			"key_kp1 = 257,"
			"key_kp2 = 258,"
			"key_kp3 = 259,"
			"key_kp4 = 260,"
			"key_kp5 = 261,"
			"key_kp6 = 262,"
			"key_kp7 = 263,"
			"key_kp8 = 264,"
			"key_kp9 = 265,"
			"key_kp_period = 266,"
			"key_kp_divide = 267,"
			"key_kp_multiply = 268,"
			"key_kp_minus = 269,"
			"key_kp_plus = 270,"
			"key_kp_enter = 271,"
			"key_kp_equals = 272,"

			"key_up = 273,"
			"key_down = 274,"
			"key_right = 275,"
			"key_left = 276,"
			"key_insert = 277,"
			"key_home = 278,"
			"key_end = 279,"
			"key_pageup = 280,"
			"key_pagedown = 281,"

			"key_f1 = 282,"
			"key_f2 = 283,"
			"key_f3 = 284,"
			"key_f4 = 285,"
			"key_f5 = 286,"
			"key_f6 = 287,"
			"key_f7 = 288,"
			"key_f8 = 289,"
			"key_f9 = 290,"
			"key_f10 = 291,"
			"key_f11 = 292,"
			"key_f12 = 293,"
			"key_f13 = 294,"
			"key_f14 = 295,"
			"key_f15 = 296,"

			"key_numlock = 300,"
			"key_capslock = 301,"
			"key_scrollock = 302,"
			"key_rshift = 303,"
			"key_lshift = 304,"
			"key_rctrl = 305,"
			"key_lctrl = 306,"
			"key_ralt = 307,"
			"key_lalt = 308,"
			"key_rmeta = 309,"
			"key_lmeta = 310,"
			"key_lsuper = 311,"
			"key_rsuper = 312,"
			"key_mode = 313,"
			"key_compose = 314,"

			"key_help = 315,"
			"key_print = 316,"
			"key_sysreq = 317,"
			"key_break = 318,"
			"key_menu = 319,"
			"key_power = 320,"
			"key_euro = 321,"
			"key_undo = 322,"

			"mouse_left  = 1,"
			"mouse_middle  = 2,"
			"mouse_right  = 3,"
			"mouse_wheelup  = 4,"
			"mouse_wheeldown  = 5,"

			"align_left = 0,"
			"align_right = 1,"
			"align_center = 2,"

			"mode_loop = 1,"
			"mode_once = 2,"
			"mode_bounce = 3,"

			"blend_normal = 0,"
			"blend_additive = 1,"
			"color_normal = 0,"
			"color_modulate = 1,"

			"file_write = 0,"
			"file_read = 1,"
			"file_append = 2,"
			"dir_game = 3,"
			"dir_save = 4,"

			"draw_line = 1,"
			"draw_fill = 2,"
			
			"line_smooth = 1,"
			"line_rough = 2,"

			"image_optimize = 1,"
			"image_pad = 2,"
			"image_pad_and_optimize = 3,"
			
			"default_font = 0,"
			"default_logo_128 = 1,"
			"default_logo_256 = 2,"
			"default_moose = 3"
			
			"}"
			);

		return true;
	}

	bool LuaVM::require(fptr_luaopen lib)
	{
		lib(L);
		return true;
	}

	void LuaVM::close()
	{
		// End Lua-state
		lua_close(L);
	}

	bool LuaVM::load(pFile file)
	{
		int result = luaL_loadbuffer (	L,
										(const char *)file->getData(), 
										file->getSize(),
										file->getFilename().c_str());

		// Could not load file, for some reason.
		if(result != 0)
		{
			// Get error message.
			const char * msg = lua_tostring(L, -1);
			lua_pop(L, 1);

			std::string str(msg);

			if(result == LUA_ERRSYNTAX)
				str = "Syntax error: " + str;
			else if(result == LUA_ERRMEM)
				str = "Memory allocation error: " + str;
			else
				str = "Error: " + str;

			// Make error message prettier.
			str = string_find_replace(str, "[string \"", "");
			str = string_find_replace(str, "\t", "");
			str = string_find_replace(str, ".lua\"]:", ".lua:");

			// Send to love error handler.
			love::error(str.c_str());

			return false;
		}

		// Run the loaded chunk.
		int status = call(0);
		handleError(status);

		return (status == 0);
	}

	bool LuaVM::load(const std::string & str)
	{
		int result = luaL_loadstring(L, str.c_str());

		// Could not load file, for some reason.
		if(result != 0)
		{
			// Get error message.
			const char * msg = lua_tostring(L, -1);
			lua_pop(L, 1);
			printf("%s\n", msg);

			return false;
		}

		// Run the loaded chunk.
		int status = call(0);
		handleError(status);

		return (status == 0);
	}

	bool LuaVM::isFunction(const std::string & function)
	{
		lua_pushstring(L, function.c_str());
		lua_rawget(L, LUA_GLOBALSINDEX);

		if(lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return true;
		}

		lua_pop(L, 1);
		return false;
	}

	bool LuaVM::isFunction(const std::string & table, const std::string & function)
	{
		lua_pushstring(L, table.c_str());
		lua_rawget(L, LUA_GLOBALSINDEX);

		if(lua_istable(L, -1))
		{
			lua_pushstring(L, function.c_str());
			lua_rawget(L, -2);
			bool result = lua_isfunction(L, -1);
			lua_pop(L, 2);
			return result;
		}else
		{
			lua_pop(L, 1);
			return false;
		}
	}

	void LuaVM::call(const std::string & function)
	{
		lua_getglobal(L, function.c_str());
		int status = call(0);
		handleError(status);
	}

	void LuaVM::calln(const std::string & function, float n)
	{
		lua_getglobal(L, function.c_str());
		lua_pushnumber(L, n);
		int status = call(1);
		handleError(status);
	}

	void LuaVM::call3n(const std::string & function, float n1, float n2, float n3)
	{
		lua_getglobal(L, function.c_str());
		lua_pushnumber(L, n1);
		lua_pushnumber(L, n2);
		lua_pushnumber(L, n3);
		int status = call(3);
		handleError(status);
	}

	void LuaVM::call1n2n(const std::string & table, const std::string & function, float n, float & r1, float & r2)
	{
		lua_getglobal(L, table.c_str()); // Push table
		lua_getfield(L, 1, function.c_str());	// Push render

		// Params
		lua_pushnumber(L, n);

		int status = call(1, 2);
		handleError(status);

		// Return values. (Reverse order)
		if(lua_isnumber(L, -1))
		{
			r2 = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
		}
		if(lua_isnumber(L, -1))
		{
			r1 = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
		}

		lua_pop(L, 1);				// Pops table
	}

	int LuaVM::call(int narg, int nres)
	{
		int status;
		int base = lua_gettop(L) - narg;  /* function index */
		lua_pushcfunction(L, lua_runtime_error);  /* push traceback function */
		lua_insert(L, base);  /* put it under chunk and args */
		status = lua_pcall(L, narg, nres, base);
		lua_remove(L, base);  /* remove traceback function */
		/* force a complete garbage collection in case of errors */
		if (status != 0) lua_gc(L, LUA_GCCOLLECT, 0);
		return status;
	}

	void LuaVM::error(const std::string & error)
	{
		luaL_error(L, error.c_str());
	}

	void LuaVM::handleError(int state)
	{
		switch (state)
		{

		// In case of run-time errors, lua_runtime_error is also called by Lua. 
		// (Most of the errors in Lua are run-time errors)
		case LUA_ERRRUN:
			break;

		// This is actually all the error codes, but
		// writing them here anyway for eventual specialization.
		case LUA_YIELD:
		case LUA_ERRSYNTAX:
		case LUA_ERRMEM:
		case LUA_ERRERR:
			
			// This is the human readable error message.
			const char * msg = lua_tostring(L, -1);

			// Remove error message.
			lua_pop(L, 1);

			// Print error message.
			//printf("%s\n", msg);
			love::error(msg);
			break;
		}
	}


	/**
	* Functions outside LuaVM.
	**/

	/**
	* Replaces all occurences of something 
	**/
	std::string string_find_replace( std::string haystack, std::string needle, std::string replace)
	{
		std::string::size_type found_at = haystack.find( needle );
		while( std::string::npos != found_at )
		{
			haystack.replace( found_at, needle.length(), replace );
			found_at = haystack.find( needle, found_at + needle.length() );
		}
		return haystack;
	}

	// Calls traceback in case of runtime errors.
	int lua_runtime_error(lua_State * L)
	{
		lua_getfield(L, LUA_GLOBALSINDEX, "debug");
		if (!lua_istable(L, -1)) {
			lua_pop(L, 1);
			return 1;
		}
		lua_getfield(L, -1, "traceback");
		if (!lua_isfunction(L, -1)) {
			lua_pop(L, 2);
			return 1;
		}
		lua_pushvalue(L, 1);  /* pass error message */
		lua_pushinteger(L, 2);  /* skip this function and traceback */
		lua_call(L, 2, 1);  /* call debug.traceback */

		// Extract message.

		if(lua_isstring(L, -1))
		{
			// For future reference. msg now holds the complete error message (with stack trace).
			const char * msg = lua_tostring(L, -1);

			std::string str = "Run-time error: " + std::string(msg);

			// Make error message prettier.
			str = string_find_replace(str, "[string \"", "");
			str = string_find_replace(str, "stack traceback:", "[error]\nStack traceback:");
			str = string_find_replace(str, "\t", "");
			str = string_find_replace(str, ".lua\"]:", ".lua:");
			str += "\n[/error]\n";

			// Send to love error handler.
			love::error(str.c_str());
		}

		return 1;
	}
		
} // love

