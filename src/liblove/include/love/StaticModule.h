/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_STATIC_MODULE_H
#define LOVE_STATIC_MODULE_H

// LOVE
#include "Module.h"

namespace love
{
	/**
	* @author Anders Ruud
	* @date 2008-07-02
	**/
	class StaticModule : public Module
	{
	public:

		/**
		* Creates a new StaticModule.
		**/
		StaticModule(fptr_init init, fptr_quit quit, fptr_open open);

		/**
		* Calls unload.
		**/
		~StaticModule();

		/**
		* Loads this StaticModule.
		**/
		bool load();

		/**
		* Unloads this StaticModule.
		**/
		void unload();

	}; // StaticModule

	typedef boost::shared_ptr<StaticModule> pStaticModule;

} // love

#endif // LOVE_STATIC_MODULE_H
