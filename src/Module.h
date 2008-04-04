/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_MODULE_H
#define LOVE_MODULE_H

// LOVE
#include "love.h"
#include "mod.h"

// STD
#include <typeinfo>
#include <map>

// Lua
struct lua_State;

namespace love
{

	// Forward declarations.
	class Filesystem;

	// Common function typedefs.
	typedef bool (*fptr_init)(love_mod::modconf *);
	typedef bool (*fptr_initfs)(int, char**, Filesystem * fs);
	typedef int  (*fptr_luaopen)(lua_State * L);
	typedef bool (*fptr_quit)();
	typedef void (*fptr_void)();
	typedef bool (*fptr_bool)();
	typedef void (*fptr_void4f)(float, float, float, float);
	typedef void (*fptr_setFilesystem)(Filesystem *);
	typedef void (*fptr_str)(std::string &);
	
	/**
	* Module superclass. 
	* 
	* @author Anders Ruud
	* @date 2008-03-14
	**/
	class Module
	{
	protected:

		// Two functions that all modules have.
		fptr_init mod_init;
		fptr_quit mod_quit;
		fptr_luaopen luaopen;

		// Loaded modules (DLLs)
		static std::map<std::string, void *> attached_modules;

	public:

		/**
		* Creates a new Module.
		**/
		Module();

		virtual ~Module();

		/**
		* Gets the luaopen-function.
		**/
		fptr_luaopen getLuaOpen();

		/**
		* Inits the Module. Although it's possible to override this method, 
		* subclasses should try to use "extra" instead.
		* @param so The platform specific name of the module.
		* @param argc Number of arguments.
		* @param argv The actual arguments.
		* @param fs A filesystem handler.
		**/
		virtual bool init(const std::string & so, love_mod::modconf * conf);

		/**
		* Shuts the Module down, and performs cleanup.
		**/
		virtual bool quit();

		/**
		* Subclasses may override this to get additional function pointers.
		* @param so The platform specific name of the module.
		* @param argc Number of arguments.
		* @param argv The actual arguments.
		**/
		virtual bool extra(const std::string & so);

		//
		// Static module handling functions.
		//
	
		/**
		* This method is the all-in-one function loader function. If you try to 
		* load a function from a module which isn't loaded, it is automatically loaded
		* the first time that module is used.
		* @param T The function type to retrieve.
		* @param so Platform specific name of shared object. (love_opengl.dll)
		* @param name The name of the function to be loaded.
		* @example fptr_init init = getf<fptr_init>("love_opengl.dll", "init");
		**/ 
		template<typename T> static T getf(const std::string & so, const std::string & name);
			
		/**
		* Unloads all loaded modules.
		**/
		static bool detach_all();

	private:

		/**
		* Loads a shared object.
		**/ 
		static bool attach(const std::string & so);

		/**
		* Unloads a shared object.
		**/
		static bool detach(const std::string & so);

		/**
		* A more low-level version of getf for internal use.
		**/
		static void * getfunc(const std::string & so, const std::string & name);
		
	}; // Module

	// Must implement this template function in header file.
	template<typename T> 
	T Module::getf(const std::string & so, const std::string & name)
	{
		// Check code moved to .cpp in order to eliminate name lookup errors in GNU
		return (T)(getfunc(so, name));
	}
}

#endif // LOVE_MODULE_H
