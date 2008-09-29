/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* Represents a loadable love module.
* 
* @author Anders Ruud
* @date 2008-03-14
*/

#ifndef LOVE_MODULE_H
#define LOVE_MODULE_H

namespace love
{
	// Forward declarions.
	class Core;

	// Common function typedefs.
	typedef bool (*fptr_core)(Core *);
	
	class Module
	{
		// Friends.
		friend class Core;

	private:

		// Function pointers.
		fptr_core init, quit, open;

	public:

		/**
		* Creates a new Module.
		**/
		Module(fptr_core init, fptr_core quit, fptr_core open);

		/**
		* Calls unload.
		**/
		~Module();

	}; // Module

} // love

#endif // LOVE_MODULE_H
