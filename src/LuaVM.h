/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_LUA_VM_H
#define LOVE_LUA_VM_H

// LOVE
#include "File.h"

// Lua
extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

// STD
#include <string>

namespace love
{

	class LuaVM
	{
	private:

		// The Lua state.
		lua_State * L;

	public:

		/**
		* Creates a new Lua virtual machine.
		**/
		LuaVM();

		~LuaVM();

		/**
		* Opens the Lua VM. Opens standard libraries, etc.
		**/
		bool open();

		/**
		* Closes the Lua VM. Garbage collects all variables in 
		* the Lua virtual machine.
		**/
		void close();

		/**
		* Loads and runs a Lua file. 
		* @param file The file to load the Lua source from.
		* @return True on success, false otherwise.
		**/
		bool load(pFile file);

		/**
		* Checks if a function exists in the global table.
		**/
		bool isFunction(const std::string & function);

		/**
		* Checks if a function exists in the specified table.
		**/
		bool isFunction(const std::string & table, const std::string & function);

		/**
		* Calls a global function with no parameters or return value.
		* @param function The function name.
		**/
		void call(const std::string & function);

		/**
		* Calls a global function with one numeric parameter.
		* Example: update(dt)
		**/
		void calln(const std::string & function, float n);

		/**
		* Calls a global function with three numeric parameters.
		* Example: mousepressed(x,y,button)
		**/
		void call3n(const std::string & function, float n1, float n2, float n3);

		/**
		* Calls a method inside a table, with one numeric parameter and two numeric return values.
		**/
		void call1n2n(const std::string & table, const std::string & function, float n, float & r1, float & r2);

	private:

		/**
		* Calls the chunk currently pushed onto the stack.
		* @param narg Number of arguments.
		* @param nres Number of results.
		**/
		int call(int narg, int nres = 0);

		/**
		* Checks for errors and handles then appropriately.
		**/
		void handleError(int state);

	}; // LuaVM

} // love


#endif // LOVE_LUA_VM_H
