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
		
	private:

		/**
		* @brief Pads the image to a power of two texture.
		* Useful for < OGL2.0, which only supports these.
		**/
		void padTwoPower();

		
	}; // OpenGLImage
	
} // love

#endif // LOVE_OPENGL_IMAGE_H
