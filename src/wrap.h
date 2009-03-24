/**
* Copyright (c) 2006-2009 LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* 
* --> Visit http://love2d.org for more information! (^.^)/
**/

#ifndef LOVE_WRAP_H
#define LOVE_WRAP_H

/**
* Contains general wrapper functions for objects. For most objects, 
* the same values for the fields __index and __gc  can be used in the 
* metatable. 
**/

#include "luax.h"

namespace love
{

	/**
	* Gets a function (or some other variable) from the
	* metatable of an object.
	**/
	int _wrap__index(lua_State * L);

	/**
	* Called when an object is collected. The object is released
	* once in this function, possibly deleting it.
	**/
	int _wrap__gc(lua_State * L);

	/**
	* Special garbage collector for Modules. This is only used
	* to trigger the quit() method on a module when it is garbage 
	* collected (which is typically when the VM is destroyed).
	**/
	int _wrap__Module_gc(lua_State * L);

} // love

#endif // LOVE_WRAP_H
