/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-31
**/

#include "SpriteBatch.h"

// STD
#include <iostream>

namespace love
{
namespace opengl
{
	SpriteBatch::SpriteBatch(Image * image, int size)
		: image(image), size(size)
	{
		image->retain();
	}

	SpriteBatch::~SpriteBatch()
	{
		image->release();
	}
} // opengl
} // love
