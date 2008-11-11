/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-31
**/

#include "Drawable.h"

namespace love
{

	Drawable::Drawable()
		: offsetX(0), offsetY(0)
	{
	}

	Drawable::~Drawable()
	{
	}

	void Drawable::setOffset(float x, float y)
	{
		this->offsetX = x;
		this->offsetY = y;
	}

	float Drawable::getOffsetX() const
	{
		return offsetX;
	}

	float Drawable::getOffsetY() const
	{
		return offsetY;
	}


} // love
