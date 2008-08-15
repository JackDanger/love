#include "LuaGame.h"

// LOVE
#include <love/Exception.h>

// STD
#include <iostream>

namespace love_system
{
	// Runtime error callback.
	extern int runtime_error(lua_State * L);
	extern void compile_error(lua_State * L, int status);

	LuaGame::LuaGame(love::pFile file, love::Core * core) 
		: Game(file), core(core), L(0)
	{
	}

	LuaGame::~LuaGame()
	{
		unload();
	}

	bool LuaGame::load()
	{
		// Create a new Lua state.
		L = lua_open();

		// Standard libs.
		luaL_openlibs(L);

		// Create the love namespace and install constants.
		installConstants();

		// Rename load. (Prevents the built-in load from 
		// being detected.
		luaL_dostring(L, "stdload = load; load = nil; love.refs = {}");

		// Custom libs.
		if(!core->open((void*)L))
			return false;

		// Load the file serving as the entry point.
		if(!parse(file))
			return false;

		// Check for present functions.
		for(int i =0;i<CALLBACK_SIZE;i++) callbacks[i] = false;
		if(isFunction("load")) callbacks[CALLBACK_LOAD] = true;
		if(isFunction("update")) callbacks[CALLBACK_UPDATE] = true;
		if(isFunction("draw")) callbacks[CALLBACK_DRAW] = true;
		if(isFunction("keypressed")) callbacks[CALLBACK_KEYPRESSED] = true;
		if(isFunction("keyreleased")) callbacks[CALLBACK_KEYRELEASED] = true;
		if(isFunction("mousepressed")) callbacks[CALLBACK_MOUSEPRESSED] = true;
		if(isFunction("mousereleased")) callbacks[CALLBACK_MOUSERELEASED] = true;
		if(isFunction("gamepadaxismoved")) callbacks[CALLBACK_GAMEPADAXISMOVED] = true;
		if(isFunction("gamepadbuttonpressed")) callbacks[CALLBACK_GAMEPADBUTTONPRESSED] = true;
		if(isFunction("gamepadbuttonreleased")) callbacks[CALLBACK_GAMEPADBUTTONRELEASED] = true;
		if(isFunction("gamepadballmoved")) callbacks[CALLBACK_GAMEPADBALLMOVED] = true;
		if(isFunction("gamepadhatmoved")) callbacks[CALLBACK_GAMEPADHATMOVED] = true;
		if(isFunction("message")) callbacks[CALLBACK_MESSAGE] = true;
		if(isFunction("event")) callbacks[CALLBACK_EVENT] = true;

		// Call load, if present.
		if(callbacks[CALLBACK_LOAD])
		{
			lua_getglobal(L, "load");
			call(0, 0);
		}

		return true;
	}

	void LuaGame::unload()
	{
		if(L == 0)
			return;
		lua_close(L);
		L = 0;
	}

	bool LuaGame::isLoaded() const
	{
		return (L != 0);
	}

	void LuaGame::update(float dt)
	{
		if(!callbacks[CALLBACK_UPDATE])
			return;
		lua_getglobal(L, "update");
		lua_pushnumber(L, dt);
		call(1, 0);
	}

	void LuaGame::draw()
	{
		if(!callbacks[CALLBACK_DRAW]) 
			return;
		lua_getglobal(L, "draw");
		call(0, 0);
	}

	void LuaGame::keyPressed(int key)
	{
		if(!callbacks[CALLBACK_KEYPRESSED])
			return;
		lua_getglobal(L, "keypressed");
		lua_pushnumber(L, key);
		call(1, 0);
	}

	void LuaGame::keyReleased(int key)
	{
		if(!callbacks[CALLBACK_KEYRELEASED])
			return;
		lua_getglobal(L, "keyreleased");
		lua_pushnumber(L, key);
		call(1, 0);
	}

	void LuaGame::mousePressed(int x, int y, int button)
	{
		if(!callbacks[CALLBACK_MOUSEPRESSED])
			return;
		lua_getglobal(L, "mousepressed");
		lua_pushnumber(L, x);
		lua_pushnumber(L, y);
		lua_pushnumber(L, button);
		call(3, 0);
	}

	void LuaGame::mouseReleased(int x, int y, int button)
	{
		if(!callbacks[CALLBACK_MOUSERELEASED])
			return;
		lua_getglobal(L, "mousereleased");
		lua_pushnumber(L, x);
		lua_pushnumber(L, y);
		lua_pushnumber(L, button);
		call(3, 0);		
	}

	void LuaGame::mouseMoved(int xrel, int yrel)
	{
		if(!callbacks[CALLBACK_MOUSEMOVED])
			return;
		lua_getglobal(L, "mousemoved");
		lua_pushnumber(L, xrel);
		lua_pushnumber(L, yrel);
		call(2, 0);
	}

	void LuaGame::gamepadAxisMoved(int index, int axis, int value)
	{
		if(!callbacks[CALLBACK_GAMEPADAXISMOVED])
			return;
		lua_getglobal(L, "gamepadaxismoved");
		lua_pushnumber(L, index);
		lua_pushnumber(L, axis);
		lua_pushnumber(L, value);
		call(3, 0);
	}

	void LuaGame::gamepadButtonPressed(int index, int button)
	{
		if(!callbacks[CALLBACK_GAMEPADBUTTONPRESSED])
			return;
		lua_getglobal(L, "gamepadbuttonpressed");
		lua_pushnumber(L, index);
		lua_pushnumber(L, button);
		call(2, 0);
	}

	void LuaGame::gamepadButtonReleased(int index, int button)
	{
		if(!callbacks[CALLBACK_GAMEPADBUTTONRELEASED])
			return;
		lua_getglobal(L, "gamepadbuttonreleased");
		lua_pushnumber(L, index);
		lua_pushnumber(L, button);
		call(2, 0);
	}

	void LuaGame::gamepadBallMoved(int index, int ball, int x, int y)
	{
		if(!callbacks[CALLBACK_GAMEPADBALLMOVED])
			return;
		lua_getglobal(L, "gamepadballmoved");
		lua_pushnumber(L, index);
		lua_pushnumber(L, ball);
		lua_pushnumber(L, x);
		lua_pushnumber(L, y);
		call(4, 0);
	}

	void LuaGame::gamepadHatMoved(int index, int hat, int direction)
	{
		if(!callbacks[CALLBACK_GAMEPADHATMOVED])
			return;
		lua_getglobal(L, "gamepadhatmoved");
		lua_pushnumber(L, index);
		lua_pushnumber(L, hat);
		lua_pushnumber(L, direction);
		call(3, 0);
	}

	void LuaGame::message(const char * msg, int tag)
	{
		if(!callbacks[CALLBACK_MESSAGE])
			return;
		lua_getglobal(L, "message");
		lua_pushstring(L, msg);
		lua_pushnumber(L, tag);
		call(2, 0);
	}


	bool LuaGame::parse(love::pFile file)
	{
		if(!file->load())
			return false;

		int status = luaL_loadbuffer (L, (const char *)file->getData(), 
			file->getSize(), file->getFilename().c_str());

		if(status != 0)
		{
			// Important that this returns true, not false.
			compile_error(L, status);
			return true;
		}

		// Run the loaded chunk.
		call(0, 0);

		return true;
	}

	bool LuaGame::isFunction(const std::string function)
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

	int LuaGame::call(int narg, int nres)
	{
		int status;
		int base = lua_gettop(L) - narg;  /* function index */
		lua_pushcfunction(L, runtime_error);  /* push traceback function */
		lua_insert(L, base);  /* put it under chunk and args */
		status = lua_pcall(L, narg, nres, base);
		lua_remove(L, base);  /* remove traceback function */
		/* force a complete garbage collection in case of errors */
		if (status != 0) lua_gc(L, LUA_GCCOLLECT, 0);
		return status;
	}

	void LuaGame::installConstants()
	{
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

			"tag_error = 0,"
			"tag_warning = 1,"
			"tag_info = 2,"
			"tag_command = 3,"
			"tag_incompatible = 4,"
			
			"default_font = 0,"
			"default_logo_128 = 1,"
			"default_logo_256 = 2,"
			"default_moose = 3,"
			"default_vermin = 4,"

			"point_sprite = 0,"

			"audio_loop = 0,"
			"audio_mode_mono = 1,"
			"audio_mode_stereo = 2,"
			"audio_quality_low = 11025,"
			"audio_quality_medium = 22050,"
			"audio_quality_high = 44100,"
			"audio_buffer_default = 1024,"

			"image_optimize = 1,"
			"image_pad = 2,"
			"image_pad_and_optimize = 3,"
			
			"shape_circle = 1,"
			"shape_polygon = 2,"
			"joint_distance = 3,"
			"joint_revolute = 4,"
			"joint_prismatic = 5,"
			"joint_mouse = 6,"	
			"joint_pulley = 7,"	
			"joint_gear = 8,"		

			"}"
			);
	}
}
