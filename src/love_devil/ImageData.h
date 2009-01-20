/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#ifndef LOVE_DEVIL_IMAGE_DATA_H
#define LOVE_DEVIL_IMAGE_DATA_H

// LOVE
#include "../liblove/image/ImageData.h"
#include "../liblove/filesystem/File.h"

// DevIL
#include <IL/il.h>

namespace love
{	
namespace devil
{
	class ImageData : love::ImageData
	{
	private:

		// The width of the image data.
		int width;

		// The height of the image data.
		int height;

		// The origin of the image.
		int origin;

		// The bits per pixel.
		int bpp;

		// DevIL image identifier.
		ILuint image;

	public:

		ImageData(File * file);
		ImageData(int width, int height);
		virtual ~ImageData();

		// Implements Data.
		void * getData();
		int getSize();

		// Implements ImageData.
		int getWidth();
		int getHeight();
		void setPixel(int x, int y, rgba c);
		rgba getPixel(int x, int y);

	}; // ImageData

} // devil
} // love

#endif // LOVE_DEVIL_IMAGE_DATA_H