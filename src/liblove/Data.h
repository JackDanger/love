/*
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* Represents any data 
* 
* @author Anders Ruud
* @date 2008-12-16
*/

#ifndef LOVE_DATA_H
#define LOVE_DATA_H

// LOVE
#include "Object.h"

namespace love
{	
	class Data : public Object
	{
	public:

		virtual ~Data();

		/**
		* Gets a pointer to the data.
		**/
		virtual char * getData() = 0;

		/**
		* Gets the size of the data buffer.
		**/
		virtual int getSize() = 0;

	}; // Data
} // love

#endif // LOVE_DATA_H