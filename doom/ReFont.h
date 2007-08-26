#ifndef LOVE_REFONT_H
#define LOVE_REFONT_H

#include "Object.h"
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
	/**
	* @class Font
	* @version 2.0
	* @since 1.0
	* @author Michael Enger (with great help from Sven C. Olsen)
	* @date 2007-01-15
	* @brief A class to handle fonts. Uses the library FreeType2 (available here: http://www.freetype.org/) and takes use of both their local documentation and Sven's experience.
	**/
	class ReFont : public Object
	{
	private:
		static const int MAX_CHARS = 256;
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
		 * @param fontpath A file path to the font.
		 * @param size The size of the font.
		 * @brief Initializes FreeType and creates the font by calling createList for every character (up to MAX_CHARS).
		 **/
		void createFont(const char * fontpath, unsigned int size);

		/**
		 * @param face The FT_Face containing information about the character.
		 * @param character The character in question.
		 * @brief Creates an OpenGL display list for the character (for speedy execution).
		 **/
		void createList(FT_Face face, unsigned short character);

	public:
		float size;
		int width[MAX_CHARS];

		/**
		 * @param text A string.
		 * @brief Prints the string.
		 **/
		void print(string text);

		/**
		 * @param fontname The full name of the font file (including extension).
		 * @param size The size of the font.
		 * @brief Simply appens fontname to the path of the fonts folder and calles createFont.
		 **/
		ReFont(string fontname, int size);

		/**
		 * @brief Clears the display lists and the textures.
		 **/
		~ReFont();
	};

	typedef boost::shared_ptr<ReFont> pReFont;
}

#endif