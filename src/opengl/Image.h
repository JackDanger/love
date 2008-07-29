/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_OPENGL_IMAGE_H 
#define LOVE_OPENGL_IMAGE_H 

// SDL
#include "GLee.h"
#include <SDL/SDL_opengl.h>
// LOVE
#include <love/File.h>
#include <love/Resource.h>
#include <love/constants.h>

// Module.
#include "Sprite.h"
#include "Volatile.h"


namespace love_opengl
{
	/**
	* This contains index mapping for the different
	* flip modes. 
	**/
	const int flipmap[3][8] = 
	{
		{ 0, 1, 2, 3, 4, 5, 6, 7 }, // NONE
		{ 6, 7, 4, 5, 2, 3, 0, 1 }, // VERTICAL
		{ 2, 3, 0, 1, 6, 7, 4, 5}   // HORIZONTAL
	};

	// Pixel format structures. Luminance-Alpha and RGB(A).
	// These might be useful to subclasses that need to convert images
	// to power-of-two textures, and need to work with pixel data in general.
	struct la { unsigned char l, a; };
	struct rgb { unsigned char r, g, b; };
	struct rgba { unsigned char r, g, b, a; };

	/**
	* OpenGL-specific image loader and renderer. Uses DevIL image
	* library for support for all relevant formats.
	* 
	* @author Anders Ruud
	* @date 2007-08-19
	**/
	class Image : public Sprite, public love::Resource, public Volatile
	{
	private:

		// The size of the actual texture in hardware
		// memory. This may be different to normal width/height 
		// due to power-of-two conversion. 
		int textureWidth;
		int textureHeight;

		// Contains vertex and texel information.
		float texels[8];
		float vertices[8];

		// The image's padding.
		int padding;

		// The origin of the loaded image.
		int origin;

		// DevIL image identifier.
		unsigned int image;

		// OpenGL texture identifier.
		GLuint texture;

	public:
	
		/**
		* Creates a new Image. Not that anything is ready to use
		* before load is called.
		* @param file The file from which to load the image.
		**/
		Image(love::pFile file);
		
		virtual ~Image();

		/**
		* Gets the actual width of the hardware texture.
		**/
		int getTextureWidth() const;

		/**
		* Gets the actual height of the hardware texture.
		**/
		int getTextureHeight() const;

		/**
		* Get the amout of padding in the image. (If
		* pad has been called).
		**/
		int getPadding() const;
		
		/**
		* Gets a pointer to the data.
		**/
		rgba * getData() const;

		void update(float dt);

		void draw() const;
		void draw(float x, float y) const;
		void draw(float x, float y, float angle, float sx, float sy, int flip = love::FLIP_NONE) const;
		void draw(const float * vertices, const float * texels, float x, float y, float angle, 
			float sx, float sy, float ox, float oy, int flip) const;

		void draws(float x, float y, float w, float h) const;
		void draws(float x, float y, float cx, float cy, float w, float h, float angle,
			float sx, float sy, float ox, float oy, int flip) const;

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
		
	}; // Image

	typedef boost::shared_ptr<Image> pImage;
	
} // love

#endif // LOVE_OPENGL_IMAGE_H
