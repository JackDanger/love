#ifndef LOVE_IMAGE_FONT_H
#define LOVE_IMAGE_FONT_H

#include "AbstractFile.h"
#include "AbstractImage.h"
#include "AbstractFont.h"
#include "Color.h"

namespace love
{
	/**
	* @class OpenGLImageFont
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2007-10-06
	* @brief For handling fonts derived from images. Note: This subclass of AbstractFont uses the width variable a little differently.
	**/
	class OpenGLImageFont : public AbstractFont, public AbstractImage
	{
	protected:
		pAbstractImage charImage; // a pointer to an image
		std::string glyphs; // the list of glyphs
		int coordinates[MAX_CHARS]; // to hold the x-position of every glyph

		/**
		 * @param character A single character.
		 * @brief Renders the passed character if it is present in the image.
		 **/
		void renderCharacter(char character);

	public:

		/**
		 * @param file an AbstractFile.
		 * @param glyphs A list of the characters as they appear in the image (example: " ABCD")
		 * @brief The default constructor. Constructs.
		 **/
		OpenGLImageFont(pAbstractFile file, const std::string & glyphs);

		/**
		 * @brief The deconstructor. Calls unload()
		 **/
		~OpenGLImageFont();

		/**
		 * @param text A string.
		 * @param x The x-coordinate.
		 * @param y The y-coordinate.
		 * @brief Prints the text at the set position.
		 **/
		virtual void print(std::string text, float x = 0, float y = 0);

		/**
		 * @param character A character.
		 * @param x The x-coordinate.
		 * @param y The y-coordinate.
		 * @brief Prints the character at the set position.
		 **/
		virtual void print(char character, float x = 0, float y = 0);

		/**
		 * @return The height of the font.
		 * @brief Returns the height of the font.
		 **/
		virtual float getLineHeight();

		/**
		 * @param line A line of text.
		 * @return The width of the passed string.
		 * @brief Returns the width of the passed string.
		 **/
		virtual float getLineWidth(const char * line);

		/**
		 * @brief Does some small calculations and sets the font up for printing.
		 *		  NOTE: Assumes that the passed image has been loaded already.
		 **/
		virtual int load();

		/**
		 * @brief Does nothing.
		 **/
		virtual void unload();
	};

	typedef boost::shared_ptr<OpenGLImageFont> pOpenGLImageFont;
}

#endif
