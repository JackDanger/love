/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_OPENGL_IMAGE_H 
#define LOVE_OPENGL_IMAGE_H 

// LOVE
#include "Image.h"

// STL

namespace love
{

	/**
	* OpenGL-specific image loader and renderer. Uses DevIL image
	* library for support for all relevant formats.
	* 
	* @author Anders Ruud
	* @date 2007-08-19
	**/
	class OpenGLImage : public Image
	{
	private:
	
		// DevIL image identifier.
		unsigned int image;

		// OpenGL texture identifier.
		unsigned int texture;

	public:
	
		/**
		* Creates a new OpenGLImage. Not that anything is ready to use
		* before load is called.
		* @param file The file from which to load the image.
		**/
		OpenGLImage(pFile file);
		
		virtual ~OpenGLImage();

		// From Sprite.
		void bind() const;
		void render() const;
		void render(float x, float y) const;
		void render(float x, float y, float width, float height) const;
		void render(float x, float y, float angle, float sx, float sy) const;

		// From Image.
		void render(const float * vertices, const float * texels, float x, float y, float angle, 
			float sx, float sy, float cx, float cy) const;
		bool readData();
		rgba * getData() const;
		bool toHardware();
		void freeData();
		
		// From Resource
		bool load();

		// From Resource
		void unload();
		
		/**
		* Extends color data one pixel into the area where alpha = 0.
		* This makes images artifact-free when rotated, stretched, etc.
		**/
		void extendAlpha();

		/**
		* Creates a border of transparent pixels around the Image.
		* @param overwrite False will pad the Image, thus resizing it; true
		* will keep the Image size and overwrite the pixels instead.
		**/
		void addAlphaBorder(bool overwrite = false);

	private:

		// Optional optimizations.

		/**
		* Pads the image to a power of two texture.
		* Useful for < OGL2.0, which only supports these.
		**/
		void padTwoPower();
		
	}; // OpenGLImage
	
} // love

#endif // LOVE_OPENGL_IMAGE_H
