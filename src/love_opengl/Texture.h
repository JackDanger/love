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
#include "../liblove/File.h"
#include "../liblove/Volatile.h"

namespace love
{
namespace opengl
{
	// Pixel format structures. Luminance-Alpha and RGB(A).
	// These might be useful to subclasses that need to convert images
	// to power-of-two textures, and need to work with pixel data in general.
	struct la { unsigned char l, a; };
	struct rgb { unsigned char r, g, b; };
	struct rgba { unsigned char r, g, b, a; };

	class Texture : public Object, public Volatile
	{
		// Friends.
		friend class Image;

	private:

		File * file;

		// Size of the loaded image file. These are the
		// dimensions the user needs to deal with.
		float width;
		float height;

		// The size of the actual texture in hardware
		// memory. This may be different to normal width/height 
		// due to power-of-two conversion. 
		int textureWidth;
		int textureHeight;

		// The image's padding.
		int padding;

		// The origin of the loaded image.
		int origin;

		// DevIL image identifier.
		unsigned int image;

		// OpenGL texture identifier.
		unsigned int texture;

	public:
	
		/**
		* Creates a new Image. Not that anything is ready to use
		* before load is called.
		* @param file The file from which to load the image.
		**/
		Texture(File * file);
		
		virtual ~Texture();

		/**
		* Gets the actual width of the hardware texture.
		**/
		int getTextureWidth() const;

		/**
		* Gets the actual height of the hardware texture.
		**/
		int getTextureHeight() const;

		int getWidth() const;
		int getHeight() const;

		/**
		* Get the amout of padding in the image. (If
		* pad has been called).
		**/
		int getPadding() const;
		
		/**
		* Gets a pointer to the data.
		**/
		rgba * getData() const;

		void bind() const;
		bool read();
		bool lock();
		void free();
		void optimize();
		void pad(int size = 1);
		
		// From Resource
		bool load();
		void unload();

		// From Volatile
		bool loadVolatile();
		void unloadVolatile();		

	private:

		/**
		* Pads the image to a power of two texture.
		* Useful for < OGL2.0, which only supports these.
		**/
		void padTwoPower();

		/**
		* Replace the current pixel data with this one. Assumes that
		* the image format, BPP, etc is the same.
		* @param data The new image data.
		* @param width The width of the new image data.
		* @param height The height of the new image data.
		* 
		* @note Does not delete the image data, so remember to do 
		* so yourself.
		**/
		void setPixels(rgba * data, int width, int height);

		/**
		* Returns string representations of DevIL error codes.
		* @error The error code.
		**/
		static const char * getErrorString(int error);
		
	}; // Texture	

} // opengl
} // love

#endif // LOVE_OPENGL_TEXTURE_H
