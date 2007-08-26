#include "lualove.h"
#include "lualove_types_lookup.h"
#include "love_keys.h"
#include "love_mouse.h"

#include "love.h"
#include "Core.h"
#include "AbstractFile.h"

#ifdef __cplusplus
extern "C" 
{
	int extern Love_Init(lua_State * L);
}
#endif

void extern luaPushPointer(lua_State * L, void * ptr, int type, int own);

namespace love
{

	void lualove_init(lua_State * L)
	{

		//luaL_openlibs(L);
		//Love_Init(L);

		// Create lookup table
		lualove_create_lookup();
	}

	void lualove_close(lua_State * L)
	{
		//lua_close(L);
		//
		// DO NOT DO THIS. This must only happen once. Ever.
		//lualove_clean_lookup();
	}

	bool lualove_loaddir(lua_State * L, const string & path)
	{
		// @todo Use boost::filesystem to load all files in a dir.
		return false;
	}

	bool lualove_load(lua_State * L, const string & filename)
	{
		
		// @todo Check file existence.

		// Open file
		luaL_loadfile(L, filename.c_str());
		int status = lua_pcall(L, 0, LUA_MULTRET, 0); // Do file
		lualove_check_error(L, status, "Could not load file \"" + filename + "\""); // Check for any errors.

		return true;
	}

	bool lualove_load(lua_State * L, AbstractFile * file)
	{

		file->load();
		
		int result = luaL_loadbuffer (	L,
										(const char *)file->getData(), 
										file->getSize(),
										file->getFilename().c_str());

		if(result != 0)
		{
			if(result == LUA_ERRSYNTAX)
				printf("Syntax error in %s.\n", file->getFilename());
			else if(result == LUA_ERRMEM)
				printf("Memory allocation error in %s.\n", file->getFilename());
			
			return false;
		}

		int status = lua_pcall(L, 0, LUA_MULTRET, 0); // Do file

		lualove_check_error(L, status, "Could not load file \"" + file->getFilename() + "\""); // Check for any errors.

		delete file;

		return (status == 0);

	}

	bool lualove_is_function(lua_State * L, const string & tablename, const string & functionname)
	{
		bool result = false;

		lua_pushstring(L, tablename.c_str());
		lua_rawget(L, LUA_GLOBALSINDEX);

		if(lua_istable(L, -1))
		{
			lua_pushstring(L, functionname.c_str());
			lua_rawget(L, -2);
			result = lua_isfunction(L, -1);
			lua_pop(L, 2);
		}else
		{
			lua_pop(L, 1);
		}

		return result;
	}

	bool lualove_is_function(lua_State * L, const string & functionname)
	{

		lua_pushstring(L, functionname.c_str());
		lua_rawget(L, LUA_GLOBALSINDEX);

		if(lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return true;
		}

		lua_pop(L, 1);
		return false;
	}

	void lualove_check_functions(lua_State * L, Scriptable * scriptable, int mask)
	{

		// Get table name
		string tab = scriptable->getScript();

		int methods = 0;

		// Init
		if(lualove_is_function(L, tab, "init"))
			methods |= LOVE_METHOD_INIT;

		// Update
		if(lualove_is_function(L, tab, "update"))
			methods |= LOVE_METHOD_UPDATE;

		// Render
		if(lualove_is_function(L, tab, "render"))
			methods |= LOVE_METHOD_RENDER;

		// Keypressed
		if(lualove_is_function(L, tab, "keypressed"))
			methods |= LOVE_METHOD_KEYPRESSED;

		// Keyreleased
		if(lualove_is_function(L, tab, "keyreleased"))
			methods |= LOVE_METHOD_KEYRELEASED;

		// Mousepressed
		if(lualove_is_function(L, tab, "mousepressed"))
			methods |= LOVE_METHOD_MOUSEPRESSED;

		// Mousepressed
		if(lualove_is_function(L, tab, "mousereleased"))
			methods |= LOVE_METHOD_MOUSERELEASED;

		int present_methods = methods;

		// Only allow methods in mask
		methods &= mask;

		// Check if present methods differ from allowed methods
		//if(present_methods != methods)
		// @todo Issue warning. 

		scriptable->setAvailableMethods(methods);



	}

	void lualove_check_error(lua_State * L, int status, const string & info)
	{
		if(status != 0)
		{
			printf("\nLua error: %s: %s\n", info.c_str(), lua_tostring(L, -1));
			lua_pop(L, 1); // remove error message
		}
	}

	void lualove_push_number(lua_State * L, lua_Number number)
	{
		lua_pushnumber(L, number);
	}

	void lualove_push_global_number(lua_State * L, const string & name, lua_Number number)
	{
		lua_pushnumber(L, number);
		lua_setglobal(L, name.c_str());
	}

	void lualove_push_pointer(lua_State * L, void * ptr, int type)
	{
		// @todo lookup type.
		luaPushPointer(L, ptr, lualove_get_type(type), 0);
	}

	void lualove_push_global_pointer(lua_State * L, void * ptr, const string & name, int type)
	{
		lualove_push_pointer(L, ptr, type);
		lua_setglobal(L, name.c_str());
	}


	void lualove_call_init(lua_State * L, void * ptr, const string & chunk, int type)
	{

		// This code assumes the chunk and method is available.

		lua_getglobal(L, chunk.c_str()); // Push table
		lua_getfield(L, 1, "init");	// Push init

		lualove_push_pointer(L, ptr, type);

		int status = lua_pcall(L, 1, 0, 0);			// Calls and pops init
		lualove_check_error(L, status, "Could not call " + chunk + ":init");

		lua_pop(L, 1);				// Pops table	

	}

	void lualove_call_update(lua_State * L, void * ptr, const string & chunk, int type, float dt)
	{
		// This code assumes the chunk and method is available.

		lua_getglobal(L, chunk.c_str()); // Push table
		lua_getfield(L, 1, "update");	// Push init

		lualove_push_pointer(L, ptr, type);
		lualove_push_number(L, dt);

		int status = lua_pcall(L, 2, 0, 0);			// Calls and pops init
		lualove_check_error(L, status, "Could not call " + chunk + ":init");

		lua_pop(L, 1);				// Pops table		
	}

	void lualove_call_render(lua_State * L, void * ptr, const string & chunk, int type)
	{
		lua_getglobal(L, chunk.c_str()); // Push table
		lua_getfield(L, 1, "render");	// Push init

		lualove_push_pointer(L, ptr, type);

		int status = lua_pcall(L, 1, 0, 0);			// Calls and pops init
		lualove_check_error(L, status, "Could not call " + chunk + ":init");

		lua_pop(L, 1);				// Pops table	
	}


	void lualove_call_init_noarg(lua_State * L, Scriptable * scriptable)
	{
		// This code assumes the chunk and method is available.

		lua_getglobal(L, scriptable->getScript().c_str());	// Push table
		lua_getfield(L, 1, "init");								// Push init

		int status = lua_pcall(L, 0, 0, 0);						// Calls and pops init
		lualove_check_error(L, status, "Could not call " + scriptable->getScript() + ":init");

		lua_pop(L, 1);											// Pops table
	}

	void lualove_call_update_noarg(lua_State *L, Scriptable * scriptable, float dt)
	{
		// This code assumes the chunk and method is available.

		lua_getglobal(L, scriptable->getScript().c_str()); // Push table
		lua_getfield(L, 1, "update");	// Push update

		lua_pushnumber(L, dt);		// Push dt to stack.

		int status = lua_pcall(L, 1, 0, 0);			// Calls and pops update
		lualove_check_error(L, status, "Could not call " + scriptable->getScript() + ":update");

		lua_pop(L, 1);				// Pops table
	}

	void lualove_call_render_noarg(lua_State *L, Scriptable * scriptable)
	{
		// This code assumes the chunk and method is available.

		lua_getglobal(L, scriptable->getScript().c_str()); // Push table
		lua_getfield(L, 1, "render");	// Push render

		int status = lua_pcall(L, 0, 0, 0);			// Calls and pops render
		lualove_check_error(L, status, "Could not call " + scriptable->getScript() + ":render");

		lua_pop(L, 1);				// Pops table
	}

	void lualove_call_keypressed_noarg(lua_State *L, Scriptable * scriptable, int key)
	{
		// This code assumes the chunk and method is available.

		lua_getglobal(L, scriptable->getScript().c_str()); // Push table
		lua_getfield(L, 1, "keypressed");	// Push update

		lua_pushnumber(L, key);		// Push dt to stack.

		int status = lua_pcall(L, 1, 0, 0);			// Calls and pops update
		lualove_check_error(L, status, "Could not call " + scriptable->getScript() + ":keypressed");

		lua_pop(L, 1);				// Pops table
	}

	void lualove_call_keyreleased_noarg(lua_State *L, Scriptable * scriptable, int key)
	{
		// This code assumes the chunk and method is available.

		lua_getglobal(L, scriptable->getScript().c_str()); // Push table
		lua_getfield(L, 1, "keyreleased");	

		lua_pushnumber(L, key);		

		int status = lua_pcall(L, 1, 0, 0);			
		lualove_check_error(L, status, "Could not call " + scriptable->getScript() + ":keypressed");

		lua_pop(L, 1);				// Pops table
	}	

	void lualove_call_mousepressed_noarg(lua_State *L, Scriptable * scriptable, float x, float y, int state)
	{
		// This code assumes the chunk and method is available.

		lua_getglobal(L, scriptable->getScript().c_str()); // Push table
		lua_getfield(L, 1, "mousepressed");	

		lua_pushnumber(L, x);
		lua_pushnumber(L, y);
		lua_pushnumber(L, state);

		int status = lua_pcall(L, 3, 0, 0);		
		lualove_check_error(L, status, "Could not call " + scriptable->getScript() + ":mousepressed");

		lua_pop(L, 1);				// Pops table
	}	

	void lualove_call_mousereleased_noarg(lua_State *L, Scriptable * scriptable, float x, float y, int state)
	{
		// This code assumes the chunk and method is available.

		lua_getglobal(L, scriptable->getScript().c_str()); // Push table
		lua_getfield(L, 1, "mousereleased");	

		lua_pushnumber(L, x);
		lua_pushnumber(L, y);
		lua_pushnumber(L, state);

		int status = lua_pcall(L, 3, 0, 0);		
		lualove_check_error(L, status, "Could not call " + scriptable->getScript() + ":mousereleased");

		lua_pop(L, 1);				// Pops table
	}	




	void lualove_create_table(lua_State * L, const string & name)
	{
		lua_getglobal(L, "love"); // Push love onto stack

		// Add new table
		lua_newtable(L);
		lua_setfield(L, -2, name.c_str());

		lua_settable(L, -3); // Save
		lua_pop(L, 1); // Remove love
	}

	void lualove_push_chunk_number(lua_State * L, const string & name, lua_Number number)
	{
		lua_getglobal(L, "love");	// Pushes defimage on stack

		// Create new subtable

		lua_pushstring(L, "r");
		lua_pushnumber(L, 255);
		lua_settable(L, -3);
		lua_pop(L, 1);
	}








	void lualove_push_all_globals(lua_State *L)
	{

		// Mouse
		lualove_push_global_number(L, "LOVE_MOUSE_LEFT", LOVE_MOUSE_LEFT);
		lualove_push_global_number(L, "LOVE_MOUSE_MIDDLE", LOVE_MOUSE_MIDDLE);
		lualove_push_global_number(L, "LOVE_MOUSE_RIGHT", LOVE_MOUSE_RIGHT);
		lualove_push_global_number(L, "LOVE_MOUSE_WHEELUP", LOVE_MOUSE_WHEELUP);
		lualove_push_global_number(L, "LOVE_MOUSE_WHEELDOWN", LOVE_MOUSE_WHEELDOWN);

		// Virtual key symbols
		lualove_push_global_number(L,"LOVE_KEY_LEFT", LOVE_KEY_LEFT); 
		lualove_push_global_number(L,"LOVE_KEY_RIGHT", LOVE_KEY_RIGHT); 
		lualove_push_global_number(L,"LOVE_KEY_UP", LOVE_KEY_UP); 
		lualove_push_global_number(L,"LOVE_KEY_DOWN", LOVE_KEY_DOWN);


		lualove_push_global_number(L,"LOVE_KEY_UNKNOWN", LOVE_KEY_UNKNOWN);	
		lualove_push_global_number(L,"LOVE_KEY_FIRST", LOVE_KEY_FIRST);		
		lualove_push_global_number(L,"LOVE_KEY_BACKSPACE", LOVE_KEY_BACKSPACE);		
		lualove_push_global_number(L,"LOVE_KEY_TAB", LOVE_KEY_TAB);		
		lualove_push_global_number(L,"LOVE_KEY_CLEAR", LOVE_KEY_CLEAR);	
		lualove_push_global_number(L,"LOVE_KEY_RETURN", LOVE_KEY_RETURN);
		lualove_push_global_number(L,"LOVE_KEY_PAUSE", LOVE_KEY_PAUSE);		
		lualove_push_global_number(L,"LOVE_KEY_ESCAPE", LOVE_KEY_ESCAPE);		
		lualove_push_global_number(L,"LOVE_KEY_SPACE", LOVE_KEY_SPACE);		
		lualove_push_global_number(L,"LOVE_KEY_EXCLAIM", LOVE_KEY_EXCLAIM);		
		lualove_push_global_number(L,"LOVE_KEY_QUOTEDBL", LOVE_KEY_QUOTEDBL);		
		lualove_push_global_number(L,"LOVE_KEY_HASH", LOVE_KEY_HASH);		
		lualove_push_global_number(L,"LOVE_KEY_DOLLAR", LOVE_KEY_DOLLAR);		
		lualove_push_global_number(L,"LOVE_KEY_AMPERSAND", LOVE_KEY_AMPERSAND);		
		lualove_push_global_number(L,"LOVE_KEY_QUOTE", LOVE_KEY_QUOTE);		
		lualove_push_global_number(L,"LOVE_KEY_LEFTPAREN", LOVE_KEY_LEFTPAREN);		
		lualove_push_global_number(L,"LOVE_KEY_RIGHTPAREN", LOVE_KEY_RIGHTPAREN);		
		lualove_push_global_number(L,"LOVE_KEY_ASTERISK", LOVE_KEY_ASTERISK);		
		lualove_push_global_number(L,"LOVE_KEY_PLUS", LOVE_KEY_PLUS);		
		lualove_push_global_number(L,"LOVE_KEY_COMMA", LOVE_KEY_COMMA);		
		lualove_push_global_number(L,"LOVE_KEY_MINUS", LOVE_KEY_MINUS);		
		lualove_push_global_number(L,"LOVE_KEY_PERIOD", LOVE_KEY_PERIOD);		
		lualove_push_global_number(L,"LOVE_KEY_SLASH", LOVE_KEY_SLASH);		
		lualove_push_global_number(L,"LOVE_KEY_0", LOVE_KEY_0);			
		lualove_push_global_number(L,"LOVE_KEY_1", LOVE_KEY_1);			
		lualove_push_global_number(L,"LOVE_KEY_2", LOVE_KEY_2);			
		lualove_push_global_number(L,"LOVE_KEY_3", LOVE_KEY_3);			
		lualove_push_global_number(L,"LOVE_KEY_4", LOVE_KEY_4);			
		lualove_push_global_number(L,"LOVE_KEY_5", LOVE_KEY_5);			
		lualove_push_global_number(L,"LOVE_KEY_6", LOVE_KEY_6);			
		lualove_push_global_number(L,"LOVE_KEY_7", LOVE_KEY_7);			
		lualove_push_global_number(L,"LOVE_KEY_8", LOVE_KEY_8);			
		lualove_push_global_number(L,"LOVE_KEY_9", LOVE_KEY_9);			
		lualove_push_global_number(L,"LOVE_KEY_COLON", LOVE_KEY_COLON);		
		lualove_push_global_number(L,"LOVE_KEY_SEMICOLON", LOVE_KEY_SEMICOLON);		
		lualove_push_global_number(L,"LOVE_KEY_LESS", LOVE_KEY_LESS);		
		lualove_push_global_number(L,"LOVE_KEY_EQUALS", LOVE_KEY_EQUALS);		
		lualove_push_global_number(L,"LOVE_KEY_GREATER", LOVE_KEY_GREATER);		
		lualove_push_global_number(L,"LOVE_KEY_QUESTION", LOVE_KEY_QUESTION);
		lualove_push_global_number(L,"LOVE_KEY_AT", LOVE_KEY_AT);		

		lualove_push_global_number(L,"LOVE_KEY_LEFTBRACKET", LOVE_KEY_LEFTBRACKET);
		lualove_push_global_number(L,"LOVE_KEY_BACKSLASH", LOVE_KEY_BACKSLASH);		
		lualove_push_global_number(L,"LOVE_KEY_RIGHTBRACKET", LOVE_KEY_RIGHTBRACKET);
		lualove_push_global_number(L,"LOVE_KEY_CARET", LOVE_KEY_CARET);		
		lualove_push_global_number(L,"LOVE_KEY_UNDERSCORE", LOVE_KEY_UNDERSCORE);		
		lualove_push_global_number(L,"LOVE_KEY_BACKQUOTE", LOVE_KEY_BACKQUOTE);		
		lualove_push_global_number(L,"LOVE_KEY_a", LOVE_KEY_a);			
		lualove_push_global_number(L,"LOVE_KEY_b", LOVE_KEY_b);			
		lualove_push_global_number(L,"LOVE_KEY_c", LOVE_KEY_c);			
		lualove_push_global_number(L,"LOVE_KEY_d", LOVE_KEY_d);			
		lualove_push_global_number(L,"LOVE_KEY_e", LOVE_KEY_e);			
		lualove_push_global_number(L,"LOVE_KEY_f", LOVE_KEY_f);			
		lualove_push_global_number(L,"LOVE_KEY_g", LOVE_KEY_g);		
		lualove_push_global_number(L,"LOVE_KEY_h", LOVE_KEY_h);		
		lualove_push_global_number(L,"LOVE_KEY_i", LOVE_KEY_i);	
		lualove_push_global_number(L,"LOVE_KEY_j", LOVE_KEY_j);		
		lualove_push_global_number(L,"LOVE_KEY_k", LOVE_KEY_k);		
		lualove_push_global_number(L,"LOVE_KEY_l", LOVE_KEY_l);		
		lualove_push_global_number(L,"LOVE_KEY_m", LOVE_KEY_m);		
		lualove_push_global_number(L,"LOVE_KEY_n", LOVE_KEY_n);	
		lualove_push_global_number(L,"LOVE_KEY_o", LOVE_KEY_o);	
		lualove_push_global_number(L,"LOVE_KEY_p", LOVE_KEY_p);		
		lualove_push_global_number(L,"LOVE_KEY_q", LOVE_KEY_q);	
		lualove_push_global_number(L,"LOVE_KEY_r", LOVE_KEY_r);		
		lualove_push_global_number(L,"LOVE_KEY_s", LOVE_KEY_s);		
		lualove_push_global_number(L,"LOVE_KEY_t", LOVE_KEY_t);		
		lualove_push_global_number(L,"LOVE_KEY_u", LOVE_KEY_u);			
		lualove_push_global_number(L,"LOVE_KEY_v", LOVE_KEY_v);		
		lualove_push_global_number(L,"LOVE_KEY_w", LOVE_KEY_w);	
		lualove_push_global_number(L,"LOVE_KEY_x", LOVE_KEY_x);		
		lualove_push_global_number(L,"LOVE_KEY_y", LOVE_KEY_y);		
		lualove_push_global_number(L,"LOVE_KEY_z", LOVE_KEY_z);		
		lualove_push_global_number(L,"LOVE_KEY_DELETE", LOVE_KEY_DELETE);


		lualove_push_global_number(L,"LOVE_KEY_F1",LOVE_KEY_F1);
		lualove_push_global_number(L,"LOVE_KEY_F2",LOVE_KEY_F2);
		lualove_push_global_number(L,"LOVE_KEY_F3",LOVE_KEY_F3);
		lualove_push_global_number(L,"LOVE_KEY_F4",LOVE_KEY_F4);
		lualove_push_global_number(L,"LOVE_KEY_F5",LOVE_KEY_F5);
		lualove_push_global_number(L,"LOVE_KEY_F6",LOVE_KEY_F6);
		lualove_push_global_number(L,"LOVE_KEY_F7",LOVE_KEY_F7);
		lualove_push_global_number(L,"LOVE_KEY_F8",LOVE_KEY_F8);
		lualove_push_global_number(L,"LOVE_KEY_F9",LOVE_KEY_F9);
		lualove_push_global_number(L,"LOVE_KEY_F10",LOVE_KEY_F10);
		lualove_push_global_number(L,"LOVE_KEY_F11",LOVE_KEY_F11);
		lualove_push_global_number(L,"LOVE_KEY_F12",LOVE_KEY_F12);

		lualove_push_global_number(L,"LOVE_KEY_RSHIFT",LOVE_KEY_RSHIFT);
		lualove_push_global_number(L,"LOVE_KEY_LSHIFT",LOVE_KEY_LSHIFT);
		lualove_push_global_number(L,"LOVE_KEY_RCTRL",LOVE_KEY_RCTRL);
		lualove_push_global_number(L,"LOVE_KEY_LCTRL",LOVE_KEY_LCTRL);
		lualove_push_global_number(L,"LOVE_KEY_RALT",LOVE_KEY_RALT);
		lualove_push_global_number(L,"LOVE_KEY_LALT",LOVE_KEY_LALT);

	}

}// love
