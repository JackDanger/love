/*
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_OPENGL_FONT_H
#define LOVE_OPENGL_FONT_H

// LOVE
#include "../liblove/File.h"
#include "../liblove/Volatile.h"

namespace love
{
namespace opengl
{
	/**
	* The abstractionation of the Font class (to incorporate ImageFonts)
	*
	* @author Michael Enger
	* @date 2007-10-03
	**/
	class Font : public Object, public Volatile
	{
	protected:

		File * file;

		int size;
		float lineHeight;
		float mSpacing; // modifies the spacing by multiplying it with this value

	public:
		static const unsigned int MAX_CHARS = 256;
		// The widths of each character.
		int widths[MAX_CHARS];
		int spacing[MAX_CHARS];

		/**
		* Default constructor.
		*
		* @param file The file containing the OpenGLFont data.
		* @param size The size of the OpenGLFont.
		**/
		Font(File * file, int size);
		
		virtual ~Font();

		virtual bool load() = 0;
		virtual void unload() = 0;

		/**
		* Prints the text at the designated position.
		*
		* @param text A string.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		**/
		virtual void print(std::string text, float x, float y) const = 0;

		/**
		* Prints the text at the designated position with rotation and scaling.
		*
		* @param text A string.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		* @param angle The amount of rotation.
		**/
		virtual void print(std::string text, float x, float y, float angle, float sx, float sy) const = 0;

		/**
		* Prints the character at the designated position.
		*
		* @param character A character.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		**/
		virtual void print(char character, float x, float y) const  = 0;

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

		/**
		* Sets the line height (which should be a number to multiply the font size by,
		* example: line height = 1.2 and size = 12 means that rendered line height = 12*1.2)
		* @param height The new line height.
		**/
		void setLineHeight(float height);

		/**
		* Returns the line height.
		**/
		virtual float getLineHeight() const;

		/**
		* Sets the spacing modifier (changes the spacing between the characters the
		* same way that the line height does [multiplication]).
		* Note: The spacing must be set BEFORE the font is loaded to have any effect.
		* @param amount The amount of modification.
		**/
		void setSpacing(float amount);

		/**
		* Returns the spacing modifier.
		**/
		float getSpacing() const;

	}; // Font

} // opengl
} // love

#endif // LOVE_FONT_H
