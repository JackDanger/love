/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-31
**/

#ifndef LOVE_GRAPHICS_DRAWABLE_H
#define LOVE_GRAPHICS_DRAWABLE_H

#include "../Object.h"

namespace love
{
namespace graphics
{
	class Drawable : public Object
	{
	protected:
	public:
		Drawable();
		virtual ~Drawable();
		virtual void draw(float x, float y, float angle, float sx, float sy, float ox, float oy) const = 0;
	};

} // graphics
} // love

#endif // LOVE_GRAPHICS_DRAWABLE_H
