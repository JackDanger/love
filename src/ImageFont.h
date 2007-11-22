#ifndef LOVE_IMAGE_FONT_H
#define LOVE_IMAGE_FONT_H

#include "AbstractFile.h"
#include "AbstractImage.h"
#include "AbstractFont.h"

namespace love
{
	/**
	* @class ImageFont
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2007-10-06
	* @brief For handling fonts derived from images. Note: This subclass of AbstractFont uses the width variable a little differently.
	**/
	class ImageFont : public AbstractFont
	{
	protected:
		pAbstractImage image;
		string charlist;
		int charwidth;
		int columns; // the amound of columns of characters in the image

		/**
		 * @param character A single character.
		 * @brief Renders the passed character if it is present in the image.
		 **/
		void renderChar(char character);

	public:

		/**
		 * @param image An abstract image.
		 * @param width The width of each character.
		 * @param height The height of each character.
		 * @param charlist A list of the characters as they appear in the image (example: "ABCD")
		 * @brief The default constructor. Constructs.
		 **/
		ImageFont(pAbstractImage image, int width, int height, const string & charlist);

		/**
		 * @brief The deconstructor. Calls unload()
		 **/
		~ImageFont();

		/**
		 * @param text Some text.
		 * @param x The x-coordinate.
		 * @param y The y-coordinate.
		 * @brief Prints the text at the set position.
		 **/
		virtual void print(const char * text, float x = 0, float y = 0);

		/**
		 * @param text A string.
		 * @param x The x-coordinate.
		 * @param y The y-coordinate.
		 * @brief Prints the text at the set position.
		 **/
		virtual void print(string text, float x = 0, float y = 0);

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

	typedef boost::shared_ptr<ImageFont> pImageFont;
}

#endif
