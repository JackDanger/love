/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#include "ImageData.h"

// STD
#include <iostream>

namespace love
{
namespace devil
{
	ImageData::ImageData(File * file)
	{
		// Load the file.
		if(!file->load())
		{
			std::cerr << "Could not read image." << std::endl;
			return;
		}

		// Generate DevIL image.
		image = ilGenImage();

		// Bind the image.
		ilBindImage(image);

		// Try to load the image.
		ILboolean success = ilLoadL(IL_TYPE_UNKNOWN, (void*)file->getData(), file->getSize());

		// Check for errors
		if(!success)
		{
			std::cerr << "Could decode image." << std::endl;
			return;
		}

		width = ilGetInteger(IL_IMAGE_WIDTH);
		height = ilGetInteger(IL_IMAGE_HEIGHT);
		origin = ilGetInteger(IL_IMAGE_ORIGIN);

		// Make sure the image is in RGBA format.
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		// This should always be four.
		bpp = ilGetInteger(IL_IMAGE_BPP);

		if(bpp != 4)
		{
			std::cerr << "Bits per pixel != 4" << std::endl;
			return;
		}
	}

	ImageData::ImageData(int width, int height)
		: width(width), height(height), origin(IL_ORIGIN_UPPER_LEFT), bpp(4)
	{
		// Generate DevIL image.
		image = ilGenImage();

		// Bind the image.
		ilBindImage(image);	

		ilTexImage(width, height, 0, bpp, IL_RGBA, IL_UNSIGNED_BYTE, 0);
	}

	ImageData::~ImageData()
	{
		ilDeleteImage(1);
	}

	int ImageData::getWidth()
	{
		return width;
	}

	int ImageData::getHeight()
	{
		return height;
	}

	char * ImageData::getData()
	{
		ilBindImage(image);
		return (char *)ilGetData();
	}

	int ImageData::getSize()
	{
		return width*height*bpp;
	}

	void ImageData::setPixel(int x, int y, rgba c)
	{
		int tx = x > width-1 ? width-1 : x;
		int ty = y > height-1 ? height-1 : y;
		rgba * pixels = (rgba *)getData();
		pixels[y*width+x] = c;
	}

	rgba ImageData::getPixel(int x, int y)
	{
		int tx = x > width-1 ? width-1 : x;
		int ty = y > height-1 ? height-1 : y;
		rgba * pixels = (rgba *)getData();
		return pixels[y*width+x];
	}

} // devil
} // love
