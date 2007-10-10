#ifndef LOVE_IMAGE_FONT_H
#define LOVE_IMAGE_FONT_H

#include "AbstractFile.h"
#include "AbstractImage.h"
#include "AbstractFont.h"

namespace love
{
	class ImageFont : public AbstractFont
	{
	protected:
		pAbstractImage image;
		int width;
		char * charlist;

	public:

		ImageFont(pAbstractImage image, int width, int height, char * charlist);
		~ImageFont();

		/**
		 * @param text Some text.
		 * @param x The x-coordinate.
		 * @param y The y-coordinate.
		 * @brief Prints the text at the set position.
		 **/
		virtual void print(const char * text, float x = 0, float y = 0) = 0;

		/**
		 * @param text A string.
		 * @param x The x-coordinate.
		 * @param y The y-coordinate.
		 * @brief Prints the text at the set position.
		 **/
		virtual void print(string text, float x = 0, float y = 0) = 0;

		/**
		 * @param character A character.
		 * @param x The x-coordinate.
		 * @param y The y-coordinate.
		 * @brief Prints the character at the set position.
		 **/
		virtual void print(char character, float x = 0, float y = 0) = 0;

		/**
		 * @return The height of the font.
		 * @brief Returns the height of the font.
		 **/
		virtual float getLineHeight() = 0;

		/**
		 * @param line A line of text.
		 * @return The width of the passed string.
		 * @brief Returns the width of the passed string.
		 **/
		virtual float getLineWidth(const char * line) = 0;

		virtual int load() = 0;
		virtual void unload() = 0;
	};

	typedef boost::shared_ptr<ImageFont> pImageFont;
}

#endif
