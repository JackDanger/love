/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_RESOURCE_H
#define LOVE_RESOURCE_H

// LOVE
#include "File.h"

namespace love
{

	/**
	* A resource is something which is loaded from a file.
	*
	* @author Anders Ruud
	* @date 2007-08-18
	**/
	class Resource
	{
	protected:

		// The file this resource is loaded from.
		pFile file;

	public:

		/**
		* Constructs a resource from the specified file.
		**/
		Resource(pFile file);

		virtual ~Resource();

		virtual bool load() = 0;
		bool reload();
		virtual void unload() = 0;

	}; // Resource

} // love

#endif // LOVE_RESOURCE_H
