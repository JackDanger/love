/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright � 2006-2008 LOVE Development Team
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
		int widths[MAX_CHARS]; //to hold the width of every char

		Font(pFile file, int size);
		virtual ~Font();

		/**
		* @param text A string.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		* @brief Prints the text at the set position.
		**/
		virtual void print(std::string text, float x = 0, float y = 0) const = 0;

		/**
		* @param character A character.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		* @brief Prints the character at the set position.
		**/
		virtual void print(char character, float x = 0, float y = 0)const  = 0;

		/**
		* @return The height of the font.
		* @brief Returns the height of the font.
		**/
		virtual float getLineHeight() const = 0;
		virtual float getHeight() const;

		/**
		* @param line A line of text.
		* @return The width of the passed string.
		* @brief Returns the width of the passed string.
		**/
		virtual float getLineWidth(const char * line) const = 0;
		virtual float getWidth(const char * line) const;
		virtual float getLineWidth(const std::string & line) const;
		virtual float getWidth(const std::string & line) const;
		
		/**
		* @param character A character.
		* @return The width of the passed character.
		* @brief Returns the width of the passed character.
		**/
		virtual float getWidth(const char character) const = 0;

	}; // Font

	typedef boost::shared_ptr<Font> pFont;

} // love

#endif // LOVE_FONT_H
