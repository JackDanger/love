/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_CORE_H
#define LOVE_CORE_H

// LOVE
#include "Module.h"

// STD

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

		// Loaded modules.
		std::map<std::string, pModule> modules;

		// Pointers to the modules. We need to be able to
		// refer to these by the abstract name.
		pModule mptr[Module::COUNT];

		// Function pointer to error function.
		void (*m_error)(const char *);

	public:

		/**
		* Initializes some members.
		**/
		Core();

		/**
		* Calls module_quit on all modules.
		**/
		~Core();
			
		/**
		* Attach a module to the Core. The module will be loaded immediately.
		* @param argc Number of command line arguments.
		* @param argv Command line arguments.
		* @param name The name of the module to attach. (love_opengl.dll)
		* @param The ID of the interface the module provides. (Module::GRAPHICS)
		**/
		bool insmod(int argc, char ** argv, const std::string & name, 
			unsigned int provides);

		/**
		* Attach a custom module to the Core. The module will be loaded 
		* immediately. The difference between standard modules and custom 
		* modules:
		*
		* - All the standard modules are "aware" of eachother, i.e. they
		*   may call functions in any other standard module.
		* - A standard module is not "aware" of a custom module, i.e. it
		*   can't call functions from a custom module (obviously).
		* - A custom module can, however, call functions from any
		*   of the standard modules.
		* - A custom module can also call functions from other custom
		*   modules.
		*
		* @param argc Number of command line arguments.
		* @param argv Command line arguments.
		* @param name The name of the module to attach. (love_custom.dll)
		**/
		bool insmod(int argc, char ** argv, const std::string & name);

		/**
		* Removes a module from the Core. The module will be unloaded
		* and immediately, and unattached from the executable.
		* @param name The name of the module to remove.
		**/
		bool rmmod(const std::string & name);

		/**
		* Gets a function pointer from one of the standard modules.
		* This function provides abstract means of getting some function
		* from some module. This function throws an exception if:
		* 
		* - The module isn't loaded.
		* - The function does not exist.
		* 
		* @param module The numeric ID of the standard module.
		* @param name The name of the function to load.
		* @example void * fptr = core->getf( Module::GRAPHICS, "clear" );
		**/
		void * getf(unsigned int module, const std::string & name) const;

		/**
		* Gets a function pointer from any module.
		* This function is primarily meant for loading of functions
		* from custom modules. This function throws an exception if:
		* 
		* - The module isn't loaded or doesn't exist.
		* - The function does not exist.
		* 
		* @param module The actual name of the shared object.
		* @param name The name of the function to load.
		* @example void * fptr = core->getf( "love_custom.dll", "clear" );
		**/
		void * getf(const std::string & module, const std::string & name) const;

		/**
		* Opens all Modules. This is useful when love.system needs
		* to create a new game.
		* @param vm A pointer to the virtual machine. (In the Lua-case, this
		*           would be the lua_State.
		**/
		bool open(void * vm);

		/**
		* Calls the error function in the system module. This 
		* will halt the current game and display the error message.
		* @param msg The message to display.
		**/
		void error(const char * msg);

	}; // Core

	typedef boost::shared_ptr<Core> pCore;

} // love

#endif // LOVE_CORE_H
