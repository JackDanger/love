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

#ifndef LOVE_GRAPHICS_OPENGL_WRAP_COLOR_H
#define LOVE_GRAPHICS_OPENGL_WRAP_COLOR_H

// LOVE
#include "../../wrap.h"
#include "Color.h"

namespace love
{
namespace graphics
{
namespace opengl
{
	Color * luax_checkcolor(lua_State * L, int idx);
	int _wrap_Color_setRed(lua_State * L);
	int _wrap_Color_setGreen(lua_State * L);
	int _wrap_Color_setBlue(lua_State * L);
	int _wrap_Color_setAlpha(lua_State * L);
	int _wrap_Color_getRed(lua_State * L);
	int _wrap_Color_getGreen(lua_State * L);
	int _wrap_Color_getBlue(lua_State * L);
	int _wrap_Color_getAlpha(lua_State * L);
	int wrap_Color_open(lua_State * L);

} // opengl
} // graphics
} // love

#endif // LOVE_GRAPHICS_OPENGL_WRAP_COLOR_H
