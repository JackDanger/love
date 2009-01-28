/*
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_OPENGL_IMAGE_FONT_H
#define LOVE_OPENGL_IMAGE_FONT_H

// Module
#include "Font.h"
#include "Texture.h"

// STD
#include <string>

namespace love
{
namespace opengl
{

	/**
	* A class to handle OpenGL image fonts.
	*
	* @author Michael Enger
	* @date 2008-01-17
	**/
	class ImageFont : public Font
	{
	protected:
		
		Texture * texture;
		
		// List of glyphs.
		std::string glyphs;
		
		// The position of each character.
		int positions[MAX_CHARS];
		
		// OpenGL display lists.
		unsigned int list;

	public:
		/**
		* Default constructor.
		*
		* @param file The image file.
		* @param glyphs A list of the characters as they appear in the image.
		**/
		ImageFont(File * file, std::string glyphs);

		/**
		* Calls unload().
		**/
		virtual ~ImageFont();


		// From Font
		virtual void print(std::string text, float x, float y) const;
		virtual void print(std::string text, float x, float y, float angle, float sx, float sy) const;
		virtual void print(char character, float x, float y) const;

		// From Resource.
		bool load();
		void unload();

		// From Volatile.
		bool loadVolatile();
		void unloadVolatile();
	
	protected:
		
		/**
		 * Returns the closest number to num which is a power of two.
		 *
		 * @param num The number to be 2powered.
		 **/
		inline int next_p2(int num);

	}; // ImageFont

} // opengl
} // love

#endif // LOVE_OPENGL_IMAGE_FONT_H
