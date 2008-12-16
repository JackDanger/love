/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
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

		// The offset of the drawable.
		float offsetX, offsetY;

	public:
		Drawable();
		virtual ~Drawable();
		virtual void draw(float x, float y, float angle, float sx, float sy) const = 0;

		/**
		* Sets the offset of the sprite. (The "center").
		**/
		virtual void setOffset(float x, float y);

		float getOffsetX() const;
		float getOffsetY() const;
	};

} // love

#endif // LOVE_DRAWABLE_H
