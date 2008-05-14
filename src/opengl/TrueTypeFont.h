/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_OPENGL_TRUETYPE_FONT_H
#define LOVE_OPENGL_TRUETYPE_FONT_H

// Module
#include "Font.h"

// FreeType2
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

// STD
#include <string>

namespace love_opengl
{

	/**
	* A class to handle TrueType fonts. Uses the library FreeType2 
	* (available here: http://www.freetype.org/) and takes use of both 
	* their local documentation and Sven's experience.
	*
	* @author Michael Enger (with great help from Sven C. Olsen) 
	* @date 2007-01-15
	**/
	class TrueTypeFont : public Font
	{
	protected:
		
		unsigned int * textures;
		unsigned int list;
		int trueHeight; // the true height of the font

		/**
		* Returns the closest number to num which is a power of two.
		*
		* @param num The number to be 2powered.
		**/
		inline int next_p2(int num);

		/**
		* As stated by Sven: A fairly straight forward function that pushes a projection matrix that will make object world coordinates identical to window coordinates.
		**/
		inline void pushScreenCoordinateMatrix();

		/**
		* Pops the projection matrix without changing the current MatrixMode.
		**/
		inline void popProjectionMatrix();

		/**
		* Creates an OpenGL display list for the character (for speedy execution).
		*
		* @param face The FT_Face containing information about the character.
		* @param character The character in question.
		**/
		void createList(FT_Face face, unsigned short character);

	public:
		/**
		* Default constructor.
		*
		* @param file The file containing the TrueTypeFont data.
		* @param size The size of the TrueTypeFont.
		**/
		TrueTypeFont(love::pFile file, int size);

		/**
		* Calls unload().
		**/
		virtual ~TrueTypeFont();


		// From Font
		//virtual float getHeight() const;
		virtual void print(std::string text, float x, float y) const;
		virtual void print(std::string text, float x, float y, float angle, float sx, float sy) const;
		virtual void print(char character, float x, float y) const;
		virtual float getHeight() const;
		virtual float getLineHeight() const;

		// From Resource.
		bool load();
		void unload();

		// From Volatile.
		bool loadVolatile();
		void unloadVolatile();

	}; // TrueTypeFont

} // love

#endif // LOVE_OPENGL_TRUETYPE_FONT_H
