#ifndef LOVE_OpenGLFont_H
#define LOVE_OpenGLFont_H

#include "AbstractFont.h"

#include "love_gl.h"
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#include <string>

#include <stdexcept>

using std::string;

namespace love
{
		
	class AbstractFile;

	/**
	* @class OpenGLFont
	* @version 2.0
	* @since 1.0
	* @author Michael Enger (with great help from Sven C. Olsen) 
	* @date 2007-01-15
	* @brief A class to handle OpenGLFonts. Uses the library FreeType2 (available here: http://www.freetype.org/) and takes use of both their local documentation and Sven's experience.
	**/
	class OpenGLFont : public AbstractFont
	{
	protected:
		
		GLuint * textures;
		GLuint list;

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
		 * @param OpenGLFontpath A file path to the OpenGLFont.
		 * @param size The size of the OpenGLFont.
		 * @brief Initializes FreeType and creates the OpenGLFont by calling createList for every character (up to MAX_CHARS).
		 **/
		void createOpenGLFont(const char * OpenGLFontpath, unsigned int size);

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
		OpenGLFont(pAbstractFile file, int size);

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
		void print(string text, float x = 0, float y = 0);

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

		virtual int load();
		virtual void unload();
	};

	typedef boost::shared_ptr<OpenGLFont> pOpenGLFont;
}

#endif