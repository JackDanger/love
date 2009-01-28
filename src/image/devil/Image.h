/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#ifndef LOVE_IMAGE_DEVIL_IMAGE_H
#define LOVE_IMAGE_DEVIL_IMAGE_H

// LOVE
#include "../../luax.h"
#include "ImageData.h"

namespace love
{
namespace image
{
namespace devil
{
	class Image
	{
	private:
		static Image * _instance;
	protected:
		Image();
	public:

		static Image * __getinstance();
		static int __advertise(lua_State * L);
		static int __open(lua_State * L);
		static int __garbagecollect(lua_State * L);
		
		int getFormats(lua_State * L);
		ImageData * newImageData(love::filesystem::File * file);
		ImageData * newImageData(int width, int height);

	}; // Image

} // devil
} // image
} // love

#endif // LOVE_IMAGE_DEVIL_IMAGE_H