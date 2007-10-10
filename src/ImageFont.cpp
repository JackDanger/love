#include "ImageFont.h"
#include "Core.h"
#include "love.h"

namespace love
{
	ImageFont::ImageFont(pAbstractImage image, int width, int height, char * charlist) : AbstractFont(0, height)
	{
		this->image = image;
		this->width = width;
		this->charlist = charlist;
	}

	ImageFont::~ImageFont()
	{
		unload();
	}

	int ImageFont::load()
	{
		//image->load(); //we assume that the fucker has been loaded already

		if(width <= 0 || height <= 0)
		{
			core->printf("ERROR: Unable to create Imagefont!");
			return LOVE_ERROR;
		}

		return LOVE_OK;
	}

	void ImageFont::unload()
	{
	}
}