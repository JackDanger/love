/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-30
**/

// LOVE
#include "Object.h"

namespace love
{

	Object::Object()
		: count(1)
	{
	}

	Object::~Object()
	{
	}

	int Object::refcount() const
	{
		return count;
	}

	void Object::retain()
	{
		++count;
	}

	void Object::release()
	{
		if(--count <= 0)
			delete this;
	}

} // love
