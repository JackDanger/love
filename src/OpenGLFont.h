/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright © 2006-2008 LOVE Development Team
*/

#ifndef LOVE_OPENGL_FONT_H
#define LOVE_OPENGL_FONT_H

// LOVE
#include "Font.h"

// FreeType2
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

// STD
#include <string>

namespace love
{

	/**
	* A class to handle OpenGLFonts. Uses the library FreeType2 
	* (available here: http://www.freetype.org/) and takes use of both 
	* their local documentation and Sven's experience.
	*
	* @author Michael Enger (with great help from Sven C. Olsen) 
	* @date 2007-01-15
	**/
	class OpenGLFont : public Font
	{
	protected:
		
		unsigned int * textures;
		unsigned int list;

		/**
		 * @param num The number to be 2powered.
		 * @return The closes number to num which is a power of two.
		 **/
		inline int next_p2(int num);

		/**
		 * @brief As stated by Sven: A fairly straight forward function that pushes a projection matrix that will make object world coordinates identical to window coordinates.
		 **/
		inline void pushScreenCoordinateMatrix();

		/**
		 * @brief Pops the projection matrix without changing the current MatrixMode.
		 **/
		inline void popProjectionMatrix();

		/**
		 * @param face The FT_Face containing information about the character.
		 * @param character The character in question.
		 * @brief Creates an OpenGL display list for the character (for speedy execution).
		 **/
		void createList(FT_Face face, unsigned short character);

	public:
		/**
		 * @param file The file containing the OpenGLFont data.
		 * @param size The size of the OpenGLFont.
		 * @brief Simply appens OpenGLFontname to the path of the OpenGLFonts folder and calles createOpenGLFont.
		 **/
		OpenGLFont(pFile file, int size);

		/**
		 * @brief Clears the display lists and the textures.
		 **/
		virtual ~OpenGLFont();

		/**
		 * @param text A string.
		 * @param x The x-coordinate.
		 * @param y The y-coordinate.
		 * @brief Prints the text at the set position.
		 **/
		void print(std::string text, float x = 0, float y = 0);

		/**
		 * @param character A character.
		 * @param x The x-coordinate.
		 * @param y The y-coordinate.
		 * @brief Prints the character at the set position.
		 **/
		void print(char character, float x = 0, float y = 0);

		/**
		 * @return The height of the OpenGLFont.
		 * @brief Returns the size of the OpenGLFont multiplied by 1.5
		 **/
		float getLineHeight();

		/**
		 * @param line A line of text.
		 * @return The width of the passed string.
		 * @brief Adds all the widths and glyph shifting values together to return the width of the line of text.
		 **/
		float getLineWidth(const char * line);

		bool load();
		void unload();

	}; // OpenGLFont

} // love

#endif // LOVE_OPENGL_FONT_H
