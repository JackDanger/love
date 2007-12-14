#ifndef LOVE_ABSTRACT_FONT_H
#define LOVE_ABSTRACT_FONT_H

#include "Object.h"
#include "Loadable.h"
#include "Resource.h"

namespace love
{
	class AbstractFile;

	/**
	* @class AbstractFont
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2007-10-03
	* @brief The abstractionation of the Font class (to incorporate ImageFonts)
	**/
	class AbstractFont : public Object, public Loadable, public Resource
	{
	protected:
		int size;

	public:
		static const unsigned int MAX_CHARS = 256;
		int widths[MAX_CHARS]; //to hold the width of every char

		AbstractFont(pAbstractFile file, int size);
		~AbstractFont();

		/**
		 * @param text A string.
		 * @param x The x-coordinate.
		 * @param y The y-coordinate.
		 * @brief Prints the text at the set position.
		 **/
		virtual void print(std::string text, float x = 0, float y = 0) = 0;

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
		virtual float getHeight();

		/**
		 * @param line A line of text.
		 * @return The width of the passed string.
		 * @brief Returns the width of the passed string.
		 **/
		virtual float getLineWidth(const char * line) = 0;
		virtual float getWidth(const char * line);

		/**
		 * @brief Abstract function.
		 **/
		virtual int load() = 0;

		/**
		 * @brief Abstract function.
		 **/
		virtual void unload() = 0;
	};

	typedef boost::shared_ptr<AbstractFont> pAbstractFont;
}

#endif
