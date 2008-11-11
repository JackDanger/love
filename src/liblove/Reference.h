/*
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development
*  
* This class wraps the reference functionality built into
* Lua, which allows C++ code to refer to Lua variables.
* 
* @author Anders Ruud
* @date 2008-08-06
*/

#ifndef LOVE_REFERENCE_H
#define LOVE_REFERENCE_H

// LOVE
#include "luax.h"

namespace love
{
	class Reference
	{
	private:

		// The Lua state in which the reference resides.
		lua_State * L;

		// Index to the Lua reference.
		int idx;

	public:

		/**
		* Creates the reference object, but does not create
		* the actual reference.
		**/
		Reference();

		/**
		* Creates the object and a reference to the value 
		* on the top of the stack.
		**/
		Reference(lua_State * L);

		/**
		* Deletes the reference, if any.
		**/
		virtual ~Reference();
		
		/**
		* Creates a reference to the value on the
		* top of the stack.
		**/ 
		void ref(lua_State * L);

		/**
		* Unrefs the reference, if any.
		**/
		void unref();

		/**
		* Pushes the referred value onto the stack.
		**/
		void push();

		/**
		* Gets the Lua state associated with this
		* reference.
		**/
		lua_State * getL();
	};

} // love

#endif // LOVE_REFERENCE_H
