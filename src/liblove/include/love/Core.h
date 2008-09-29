/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_CORE_H
#define LOVE_CORE_H

// LOVE
#include "Module.h"
#include "Game.h"

// STD
#include <vector>
#include <sstream>

namespace love
{
	/**
	* Core is briefly put the plugin manager. It also
	* contains some convenience methods for making
	* function loading less painful.
	* 
	* Oh yes. Core is back.
	*
	* @author Anders Ruud
	* @date 2008-05-09
	**/
	class Core
	{
	private:

		// All Modules, in the order they're loaded.
		std::vector<Module> modules;
		
		// The currently running state.
		lua_State * L;

	public:

		/**
		* Creates the Lua state and initializes it.
		**/
		Core();

		/**
		* Calls module_quit on all modules.
		**/
		~Core();

		/**
		* Calls love.init().
		**/
		int init();

		/**
		* Sets the arg table with the command line arguments.
		**/
		void setArg(int argc, char ** argv);

		void addSearcher(lua_CFunction f);

		/**
		* Attach a module to the Core. The module will be loaded immediately.
		* @param module The module to insert. (Will be automatically freed).
		**/
		bool insert(Module module);

		/**
		* Triggers an error.
		**/
		bool error(const char * fmt, ...);

		/**
		* Allows the core to be used as a lua_State.
		**/
		inline lua_State * getL()
		{
			return L;
		}

	}; // Core

	extern Core * core;

} // love

#endif // LOVE_CORE_H
