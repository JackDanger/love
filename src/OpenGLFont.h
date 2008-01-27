/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
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
		* @param file The file containing the OpenGLFont data.
		* @param size The size of the OpenGLFont.
		**/
		OpenGLFont(pFile file, int size);

		/**
		* Calls unload().
		**/
		virtual ~OpenGLFont();


		// From Font
		//virtual float getHeight() const;
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

	}; // OpenGLFont

} // love

#endif // LOVE_OPENGL_FONT_H
