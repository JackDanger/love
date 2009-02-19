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

#ifndef LOVE_OPENGL_TEXTURE_H
#define LOVE_OPENGL_TEXTURE_H

// LOVE
#include "../liblove/Object.h"
#include "../liblove/image/ImageData.h"
#include "../liblove/graphics/Volatile.h"

namespace love
{
namespace opengl
{

	class Texture : public Object, public Volatile
	{
		// Friends.
		friend class Image;

	private:

		ImageData * data;

		// The size of the actual texture in hardware
		// memory. This may be different to normal width/height 
		// due to power-of-two conversion. 
		int width;
		int height;

		// OpenGL texture identifier.
		unsigned int texture;

	public:
	
		/**
		* Creates a new Image. Not that anything is ready to use
		* before load is called.
		**/
		Texture(ImageData * data);
		
		virtual ~Texture();

		int getWidth() const;
		int getHeight() const;
		
		void bind() const;

		// From Resource
		bool load();
		void unload();

		// From Volatile
		bool loadVolatile();
		void unloadVolatile();		
		
	}; // Texture	

} // opengl
} // love

#endif // LOVE_OPENGL_TEXTURE_H
