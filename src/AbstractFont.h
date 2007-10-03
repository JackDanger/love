#ifndef LOVE_ABSTRACT_FONT_H
#define LOVE_ABSTRACT_FONT_H

#include "Object.h"
#include "Loadable.h"
#include "Resource.h"

namespace love
{
	class AbstractFile;

	class AbstractFont : public Object, public Loadable, public Resource
	{
	protected:
		int size;

	public:
		static const int MAX_CHARS = 256;
		int width[MAX_CHARS]; //to hold the width of every char

		AbstractFont(AbstractFile * file, int size);
		~AbstractFont();

		/**
		 * @param text Some text.
		 * @brief Prints the text.
		 **/
		virtual void print(const char * text) = 0;

		/**
		 * @param text A string.
		 * @brief Prints the text.
		 **/
		virtual void print(string text) = 0;

		/**
		 * @param text Some text.
		 * @param x The x-coordinate.
		 * @param y The y-coordinate.
		 * @brief Prints the text at the set position.
		 **/
		virtual void print(const char * text, float x, float y) = 0;

		/**
		 * @param text A string.
		 * @param x The x-coordinate.
		 * @param y The y-coordinate.
		 * @brief Prints the text at the set position.
		 **/
		virtual void print(string text, float x, float y) = 0;

		/**
		 * @param character A character.
		 * @brief Prints the character.
		 **/
		virtual void print(char character) = 0;

		/**
		 * @param character A character.
		 * @param x The x-coordinate.
		 * @param y The y-coordinate.
		 * @brief Prints the character at the set position.
		 **/
		virtual void print(char character, float x, float y) = 0;

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

	typedef boost::shared_ptr<AbstractFont> pAbstractFont;
}

#endif
