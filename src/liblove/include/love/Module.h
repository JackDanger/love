/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_MODULE_H
#define LOVE_MODULE_H

// LOVE


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
	typedef bool  (*fptr_open)(void *);
	
	/**
	* Abstract Module. 
	* 
	* @author Anders Ruud
	* @date 2008-03-14
	**/
	class Module
	{
	protected:

		// Friends.
		friend class Core;

		// Functions that all modules must have, dynamic
		// as well as static.
		fptr_init module_init;
		fptr_quit module_quit;
		fptr_open module_open;

	public:

		/**
		* Creates a new Module.
		**/
		Module();

		/**
		* Calls unload.
		**/
		virtual ~Module();

		/**
		* Loads this Module.
		**/
		virtual bool load() = 0;

		/**
		* Unloads this Module.
		**/
		virtual void unload() = 0;

	}; // Module

	typedef boost::shared_ptr<Module> pModule;

} // love

#endif // LOVE_MODULE_H
