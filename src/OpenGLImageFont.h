/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright � 2006-2008 LOVE Development Team
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
		std::string glyphs;
		// The position of each character.
		int positions[MAX_CHARS];
		
		/**
		 * Creates an OpenGL display list for the character (for speedy execution).
		 *
		 * @param character The character in question.
		 **/
		void createList(unsigned short character);

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
		void print(std::string text, float x = 0, float y = 0) const;
		void print(char character, float x = 0, float y = 0) const;

		/**
		* Loads the file and creates a series of display lists.
		**/
		bool load();
		
		/**
		* Deletes the display lists and any texture information.
		**/
		void unload();

	}; // OpenGLImageFont

} // love

#endif // LOVE_OPENGL_IMAGE_FONT_H
