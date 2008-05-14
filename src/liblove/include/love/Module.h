/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_MODULE_H
#define LOVE_MODULE_H

// LOVE

// This must be defined in Linux.
#ifndef WIN32
#define LOVE_MOD_PATH "/usr/lib/love/"
#endif


// STD
#include <string>
#include <typeinfo>
#include <map>

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{
	class Core;

	// Common function typedefs.
	typedef bool (*fptr_init)(int, char **, Core *);
	typedef bool (*fptr_quit)();
	typedef int  (*fptr_open)(void *);

	// Other common function types.
	typedef void (*fptr_void)();
	typedef bool (*fptr_bool)();
	typedef float (*fptr_float)();
	typedef void (*fptr_str)(std::string &);
	typedef char * (*fptr_cstr)();
	
	/**
	* Represents a single module. This class
	* will be responsible for loading and unloading
	* itself, as well as management of functions 
	* related to this module.
	* 
	* @author Anders Ruud
	* @date 2008-03-14
	**/
	class Module
	{
	private:

		// Friends.
		friend class Core;

		// Name of this module (the filename of the DLL/SO).
		std::string name;

		// Pointer to the DLL/SO handle.
		void * handle;

		// Functions that have been retrieved.
		std::map<std::string, void *> functions;

		// Functions that all modules must have.
		fptr_init module_init;
		fptr_quit module_quit;
		fptr_open module_open;

	public:

		/**
		* Module identifiers.
		**/
		static enum
		{
			FILESYSTEM, 
			PHYSICS, 
			GRAPHICS, 
			TIMER, 
			KEYBOARD, 
			MOUSE, 
			AUDIO, 
			SYSTEM, 
			COUNT, 
			CUSTOM
		};

		/**
		* Creates a new Module.
		**/
		Module(std::string name);

		/**
		* Calls unload.
		**/
		~Module();

		/**
		* Loads this Module.
		**/
		bool load();

		/**
		* Unloads this Module.
		**/
		void unload();

		/**
		* Gets a pointer to a function within the Module.
		**/
		void * getf(const std::string & name);

	}; // Module

	typedef boost::shared_ptr<Module> pModule;

} // love

#endif // LOVE_MODULE_H
