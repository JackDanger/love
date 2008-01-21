/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_FONT_H
#define LOVE_FONT_H

// LOVE
#include "Resource.h"

namespace love
{
	/**
	* The abstractionation of the Font class (to incorporate ImageFonts)
	*
	* @author Michael Enger
	* @date 2007-10-03
	**/
	class Font : public Resource
	{
	protected:
		int size;

	public:
		static const unsigned int MAX_CHARS = 256;
		// The widths of each character.
		int widths[MAX_CHARS];

		/**
		* Default constructor.
		*
		* @param file The file containing the OpenGLFont data.
		* @param size The size of the OpenGLFont.
		**/
		Font(pFile file, int size);
		
		virtual ~Font();

		/**
		* Prints the text at the designated position.
		*
		* @param text A string.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		**/
		virtual void print(std::string text, float x = 0, float y = 0) const = 0;

		/**
		* Prints the character at the designated position.
		*
		* @param character A character.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		**/
		virtual void print(char character, float x = 0, float y = 0) const  = 0;

		/**
		* Returns the height of the font.
		**/
		virtual float getHeight() const;

		/**
		* Returns the width of the passed string.
		*
		* @param line A line of text.
		**/
		virtual float getWidth(const std::string & line) const;
		virtual float getWidth(const char * line) const;
		
		/**
		* Returns the width of the passed character.
		*
		* @param character A character.
		**/
		virtual float getWidth(const char character) const;

	}; // Font

	typedef boost::shared_ptr<Font> pFont;

} // love

#endif // LOVE_FONT_H
