#include "Image.h"

namespace love
{

	Image::Image(pFile file) 
		: Resource(file), textureWidth(0), textureHeight(0), linger(false)
	{
	}

	Image::Image(pFile file, bool linger) 
		: Resource(file), textureWidth(0), textureHeight(0), linger(linger)
	{
	}

	Image::~Image()
	{
	}

	void Image::update(float dt)
	{
	}

}// love
