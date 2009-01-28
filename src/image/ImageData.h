/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#ifndef LOVE_IMAGE_IMAGE_DATA_H
#define LOVE_IMAGE_IMAGE_DATA_H

// LOVE
#include "../Data.h"

namespace love
{	
namespace image
{
	// Pixel format structures. Luminance-Alpha and RGB(A).
	struct la { unsigned char l, a; };
	struct rgb { unsigned char r, g, b; };
	struct rgba { unsigned char r, g, b, a; };

	class ImageData : public Data
	{
	public:

		virtual ~ImageData();

		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
		virtual void setPixel(int x, int y, rgba c) = 0;
		virtual rgba getPixel(int x, int y) = 0;

	}; // ImageData

} // image
} // love

#endif // LOVE_IMAGE_IMAGE_DATA_H