/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_CORE_H
#define LOVE_CORE_H

// LOVE
#include "DynamicModule.h"
#include "StaticModule.h"
#include "modspec.h"

// STD
#include <vector>

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

		// Command line arguments.
		int argc;
		char ** argv;

		// The standard, static modules.
		Filesystem filesystem;
		Graphics graphics;
		Timer timer;
		System system;
		Audio audio;
		Mouse mouse;
		Keyboard keyboard;
		Joystick joystick;

		// All Modules, in the order they're loaded.
		std::vector<pModule> modules;

		// Dynamic modules, accessible by name. (This only contains
		// the dynamic modules, while "modules" contain both dynamic
		// and static).
		std::map<std::string, pDynamicModule> dynamic_modules;

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
		* Sets the command line arguments.
		* @param argc Number of command line arguments.
		* @param argv Command line arguments.
		**/
		void setArgs(int argc, char ** argv);

		bool insmod(pModule m);

		/**
		* Attach a module to the Core. The module will be loaded immediately.
		* @param init Function pointer to the module init function.
		* @param quit Function pointer to the module quit function.
		* @param open Function pointer to the module (lua)open function.
		**/
		bool insmod(fptr_init init, fptr_quit quit, fptr_open open);

		bool insmod(const std::string & name);

		/**
		* Opens all Modules. This is useful when love.system needs
		* to create a new game.
		* @param vm A pointer to the virtual machine. (In the Lua-case, this
		*           would be the lua_State.
		**/
		bool open(void * vm);

		bool verify();

		/**
		* Calls the error function in the system module. This 
		* will halt the current game and display the error message.
		* @param msg The message to display.
		**/
		void error(const char * msg);

		// Accessor functions for the standard modules.
		Filesystem * getFilesystem();
		Graphics * getGraphics();
		Timer * getTimer();
		System * getSystem();
		Audio * getAudio();
		Mouse * getMouse();
		Keyboard * getKeyboard();
		Joystick * getJoystick();


	}; // Core

	typedef boost::shared_ptr<Core> pCore;

} // love

#endif // LOVE_CORE_H
