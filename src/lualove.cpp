#include "lualove.h"


#include "lualove_globals.h"
#include "ObjectFactory.h"


#include "lualove_types_lookup.h"
#include "love_keys.h"
#include "love_mouse.h"

#include "love.h"
#include "Core.h"
#include "AbstractFile.h"
#include "UIGame.h"


#ifdef __cplusplus
extern "C" 
{
	int extern Love_Init(lua_State * L);
}
#endif

void extern luaPushPointer(lua_State * L, void * ptr, int type, int own);

namespace love
{


	// From lualove_globals.
	// These will eventually reside in the love module in Lua.
	Keyboard * keyboard;
	Mouse * mouse;
	AbstractDisplay * display;
	Timer * timer;
	ObjectFactory * objects;
	AbstractGraphics * graphics;
	AbstractAudio * audio;
	LuaGame * game;
	GUIContainer * gui;


	void lualove_init(lua_State * L)
	{

		//luaL_openlibs(L);
		//Love_Init(L);

		// Create lookup table
		lualove_create_lookup();

		// Bind global pointers.
		lualove_bind_globals();

	}

	void lualove_close(lua_State * L)
	{
		//lua_close(L);
		//
		// DO NOT DO THIS. This must only happen once. Ever.
		//lualove_clean_lookup();

		// Delete allocated globals here. (from lualove_globals)
		delete objects;
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
		lualove_check_error(L, status, ""); // Check for any errors.

		return true;
	}

	bool lualove_load(lua_State * L, pAbstractFile file)
	{

		file->load();

		int result = luaL_loadbuffer (	L,
										(const char *)file->getData(), 
										file->getSize(),
										file->getFilename().c_str());

		if(result != 0)
		{
			
			const char * msg = lua_tostring(L, -1);
			lua_pop(L, 1);

			printf("%s\n", msg);
			lualove_gui_error(msg);

			return false;
		}

		int status = lualove_call(L, 0);
		lualove_handle_error(L, status);

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
		if(lualove_is_function(L, tab, "load"))
			methods |= LOVE_METHOD_LOAD;

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

		// Mousepressed
		if(lualove_is_function(L, tab, "event"))
			methods |= LOVE_METHOD_EVENT;

		// (unused) int present_methods = methods;

		// Only allow methods in mask
		methods &= mask;

		// Check if present methods differ from allowed methods
		//if(present_methods != methods)
		// @todo Issue warning. 

		scriptable->setAvailableMethods(methods);



	}

	int lualove_call(lua_State *L, int narg)
	{
		int status;
		int base = lua_gettop(L) - narg;  /* function index */
		lua_pushcfunction(L, lualove_runtime_error);  /* push traceback function */
		lua_insert(L, base);  /* put it under chunk and args */
		status = lua_pcall(L, narg, 0, base);
		lua_remove(L, base);  /* remove traceback function */
		/* force a complete garbage collection in case of errors */
		if (status != 0) lua_gc(L, LUA_GCCOLLECT, 0);
		return status;
	}

	int lualove_runtime_error(lua_State * L)
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
			// For future reference. msg now hold the complete error message (with stack trace).
			const char * msg = lua_tostring(L, -1);
			lualove_gui_error(msg);
		}

		return 1;
	}

	void lualove_gui_error(const char * message)
	{

		// Convert tabs to spaces.
		std::string str(message);


		// Replace tabs.
		for(int i = 0;i<(int)str.length();i++)
			if(str.substr(i, 1) == "\t")
				str.replace(i, 1, "    * ");


		love::core->uigame->showError(str.c_str());
	}

	void lualove_handle_error(lua_State * L, int state)
	{
		switch (state)
		{
		// This is actually all the error codes, but
		// writing them here anyway for eventual specialization.
		case LUA_YIELD:
		// In case of run-time errors, lualove_runtime_error is also called by Lua. 
		// (Most of the errors in Lua are run-time errors)
		case LUA_ERRRUN:
		case LUA_ERRSYNTAX:
		case LUA_ERRMEM:
		case LUA_ERRERR:
			
			// This is the human readable error message.
			const char * msg = lua_tostring(L, -1);

			// Remove error message.
			lua_pop(L, 1);

			// Print error message.
			printf("%s\n", msg);
			break;
		}
	}

	void lualove_check_error(lua_State * L, int status, const string & info)
	{
		if(status != 0)
		{
			printf("Error: %s\n", lua_tostring(L, -1));
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


	void lualove_call_load(lua_State * L, void * ptr, const string & chunk, int type)
	{

		// This code assumes the chunk and method is available.

		lua_getglobal(L, chunk.c_str()); // Push table
		lua_getfield(L, 1, "load");	// Push load

		lualove_push_pointer(L, ptr, type);

		int status = lualove_call(L, 1);
		lualove_handle_error(L, status);

		lua_pop(L, 1);				// Pops table	

	}

	void lualove_call_update(lua_State * L, void * ptr, const string & chunk, int type, float dt)
	{
		// This code assumes the chunk and method is available.

		lua_getglobal(L, chunk.c_str()); // Push table
		lua_getfield(L, 1, "update");	// Push updaet

		lualove_push_pointer(L, ptr, type);
		lualove_push_number(L, dt);

		int status = lualove_call(L, 2);
		lualove_handle_error(L, status);

		lua_pop(L, 1);				// Pops table		
	}

	void lualove_call_render(lua_State * L, void * ptr, const string & chunk, int type)
	{
		lua_getglobal(L, chunk.c_str()); // Push table
		lua_getfield(L, 1, "render");	// Push render

		lualove_push_pointer(L, ptr, type);

		int status = lualove_call(L, 1);
		lualove_handle_error(L, status);

		lua_pop(L, 1);				// Pops table	
	}

	void lualove_call_event(lua_State * L, Scriptable * scriptable, void * event_ptr, int type)
	{
		// This code assumes the chunk and method is available.
		lua_getglobal(L, scriptable->getScript().c_str());	// Push table
		lua_getfield(L, 1, "event");						// Push event

		// Push the event.
		lualove_push_pointer(L, event_ptr, type);
		int status = lualove_call(L, 1);
		lualove_handle_error(L, status);
		lua_pop(L, 1);				// Pops table	
	}

	void lualove_call_load_noarg(lua_State * L, Scriptable * scriptable)
	{
		// This code assumes the chunk and method is available.

		lua_getglobal(L, scriptable->getScript().c_str());	// Push table
		lua_getfield(L, 1, "load");								// Push load

		int status = lualove_call(L, 0);
		lualove_handle_error(L, status);

		lua_pop(L, 1);											// Pops table
	}

	void lualove_call_update_noarg(lua_State *L, Scriptable * scriptable, float dt)
	{
		// This code assumes the chunk and method is available.

		lua_getglobal(L, scriptable->getScript().c_str()); // Push table
		lua_getfield(L, 1, "update");	// Push update

		lua_pushnumber(L, dt);		// Push dt to stack.

		int status = lualove_call(L, 1);
		lualove_handle_error(L, status);

		lua_pop(L, 1);				// Pops table
	}

	void lualove_call_render_noarg(lua_State *L, Scriptable * scriptable)
	{
		// This code assumes the chunk and method is available.

		lua_getglobal(L, scriptable->getScript().c_str()); // Push table
		lua_getfield(L, 1, "render");	// Push render

		int status = lualove_call(L, 0);
		lualove_handle_error(L, status);

		lua_pop(L, 1);				// Pops table
	}

	void lualove_call_keypressed_noarg(lua_State *L, Scriptable * scriptable, int key)
	{
		// This code assumes the chunk and method is available.

		lua_getglobal(L, scriptable->getScript().c_str()); // Push table
		lua_getfield(L, 1, "keypressed");	// Push update

		lua_pushnumber(L, key);		// Push dt to stack.

		int status = lualove_call(L, 1);
		lualove_handle_error(L, status);

		lua_pop(L, 1);				// Pops table
	}

	void lualove_call_keyreleased_noarg(lua_State *L, Scriptable * scriptable, int key)
	{
		// This code assumes the chunk and method is available.

		lua_getglobal(L, scriptable->getScript().c_str()); // Push table
		lua_getfield(L, 1, "keyreleased");	

		lua_pushnumber(L, key);		

		int status = lualove_call(L, 1);
		lualove_handle_error(L, status);

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

		int status = lualove_call(L, 3);
		lualove_handle_error(L, status);

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

		int status = lualove_call(L, 3);
		lualove_handle_error(L, status);

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

	}

	void lualove_bind_globals()
	{
		keyboard = core->keyboard;
		mouse = core->mouse;
		display = core->display;
		timer = core->timer;
		objects = new ObjectFactory();
		graphics = core->graphics;
		audio = core->audio;
		game = 0;
		gui = 0;
	}

}// love
