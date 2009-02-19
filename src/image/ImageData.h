/**
* LOVE -- Free 2D Game Engine
* Version $(DOC_VERSION), $(DOC_DATE)
* 
* Copyright (c) 2006-$(DOC_YEAR) LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* 
* -- LOVE Development Team, http://love2d.org
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