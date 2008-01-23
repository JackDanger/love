/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_OPENGL_IMAGE_FONT_H
#define LOVE_OPENGL_IMAGE_FONT_H

// LOVE
#include "Font.h"
#include "Image.h"

// STD
#include <string>

namespace love
{

	/**
	* A class to handle OpenGL image fonts.
	*
	* @author Michael Enger
	* @date 2008-01-17
	**/
	class OpenGLImageFont : public Font
	{
	protected:
		// The formatted image.
		pImage image;
		
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
		OpenGLImageFont(pFile file, std::string glyphs);

		/**
		* Calls unload().
		**/
		virtual ~OpenGLImageFont();


		// From Font
		virtual void print(std::string text, float x = 0, float y = 0) const;
		virtual void print(char character, float x = 0, float y = 0) const;

		/**
		* Loads the file and creates a series of display lists.
		**/
		virtual bool load();
		
		/**
		* Deletes the display lists and any texture information.
		**/
		virtual void unload();
	
	protected:
		
		/**
		 * Returns the closest number to num which is a power of two.
		 *
		 * @param num The number to be 2powered.
		 **/
		inline int next_p2(int num);

	}; // OpenGLImageFont

} // love

#endif // LOVE_OPENGL_IMAGE_FONT_H
