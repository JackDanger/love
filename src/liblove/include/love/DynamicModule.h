/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_DYNAMIC_MODULE_H
#define LOVE_DYNAMIC_MODULE_H

// LOVE
#include "Module.h"

namespace love
{
	
	/**
	* @author Anders Ruud
	* @date 2008-07-02
	**/
	class DynamicModule : public Module
	{
	private:

		// Name of this module (the filename of the DLL/SO).
		std::string name;

		// Pointer to the DLL/SO handle.
		void * handle;

		// Functions that have been retrieved.
		std::map<std::string, void *> functions;

	public:

		/**
		* Creates a new DynamicModule.
		**/
		DynamicModule(std::string name);

		/**
		* Calls unload.
		**/
		~DynamicModule();

		/**
		* Loads this DynamicModule.
		**/
		bool load();

		/**
		* Unloads this DynamicModule.
		**/
		void unload();

		/**
		* Gets a pointer to a function within the DynamicModule.
		**/
		void * getf(const std::string & name);

	}; // DynamicModule

	typedef boost::shared_ptr<DynamicModule> pDynamicModule;

} // love

#endif // LOVE_DYNAMIC_MODULE_H
