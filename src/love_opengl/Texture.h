/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-31
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
