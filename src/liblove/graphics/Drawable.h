/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-31
**/

#ifndef LOVE_DRAWABLE_H
#define LOVE_DRAWABLE_H

#include "../Object.h"

namespace love
{
	class Drawable : public Object
	{
	protected:
	public:
		Drawable();
		virtual ~Drawable();
		virtual void draw(float x, float y, float angle, float sx, float sy, float ox, float oy) const = 0;
	};

} // love

#endif // LOVE_DRAWABLE_H
