/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* This file is to be included in every module. It 
* contains some preprocessor definitions, includes
* common header files and provides functionlity 
* that is used in many modules. 
* 
* When making changes to this file, keep in mind
* that each module will get a private copy of
* everything: noting is shared between them.
* 
* @author Anders Ruud
* @date 2008-03-17
*/

#ifndef LOVE_MOD_H
#define LOVE_MOD_H

// For correct linkage across compilers.
#ifdef WIN32
#	define DECLSPEC __declspec(dllexport)
#else
#	define DECLSPEC
#endif

// All modules need Lua.
extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

// STD
#include <string>
#include <iostream>

// Forward declarations.
namespace love
{
	class Filesystem;
} // love

/**
* The love_mod namespace contains code 
* that each module uses.
**/
namespace love_mod
{
	// Function pointers.
	typedef void (*fptr_print)(const char * str);
	typedef void (*fptr_error)(const char * str);

	/**
	* Module configuration. This is what a module
	* needs to know to initialize.
	**/
	struct modconf
	{
		int argc;					// Number of arguments.
		char ** argv;				// List of arguments.
		fptr_print print;			// Function for console printing.
		fptr_error error;			// Function for raising error.
		love::Filesystem * filesystem;	// Only used by modfs-modules.
	};

	/**
	* Sets the current Lua state. This must be set during 
	* module initialization, or many of the functions won't work.
	* @param s The new Lua state.
	**/
	void setL( lua_State * s );

	/**
	* Gets a pointer to the current Lua state.
	**/
	lua_State * getL();

	/**
	* Sets the module configuration. This must
	* be set for error and print to work.
	**/
	void setConf(modconf * c);

	/**
	* Raises an error with the error message
	* in str. (Modconf must be set).
	**/
	void error(const std::string & str);

	/**
	* Prints str to stdout and graphically in 
	* the console. (Modconf must be set).
	**/
	void print(const std::string & str);

	/**
	* Triggers a run-time error. It only makes
	* sense to use this if the offending function
	* is triggered from Lua. 
	* @param e The error message to display.
	**/
	void runtime_error( const std::string & e );

	/**
	* Loads and runs a string as Lua code. At the time 
	* of writing, it's main use is setting the devices
	* to the correct modules (see example).
	* @param s The string to run as Lua code.
	* @example do_string("love.graphics = mod_opengl");
	**/
	void do_string( const std::string & s );

	/**
	* Pretty-prints info about the module to stdout.
	* It's not necessary to call this, it's mostly for 
	* debug purposes.
	* @param device The love-device this module provices.
	* @param provider The libraries that provide the functionality.
	* @example report_init("love.audio", "SDL_mixer");
	**/
	void report_init( const std::string & device, const std::string & provider );

	/**
	* Calls the chunk currently pushed onto the stack.
	* @param narg Number of arguments.
	* @param nres Number of results.
	**/
	int call(int narg, int nres = 0);

	/**
	* Checks for errors and handles then appropriately.
	**/
	void handle_error(int state);

	/**
	* This method is called if a runtime error occurs as
	* a result of call().
	**/
	int runtime_error_callback(lua_State * L);
}

#endif // LOVE_MOD_H
