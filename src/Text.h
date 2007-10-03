#ifndef LOVE_TEXT_H
#define LOVE_TEXT_H

#include <string>
#include <vector>

#include "Object.h"
#include "Font.h"
#include "Color.h"
#include "Updateable.h"
#include "Container.h"

using std::string;
using std::vector;

namespace love
{
		/**
		* @class Text
		* @version 1.0
		* @since 1.0
		* @author Michael Enger
		* @date 2006-09-03
		* @brief Used to handle the output of text (in the selected Font and Color).
		**/
	class Text : public Object, public Loadable
	{
	private:
		// define ^.^
		const static int MAX_SIZE = 5000; //who needs more space than this?

		vector<string> lines; //the lines of text
		AbstractColor * color; //the current color
		Font * font; //the current font
		pColor defaultColor;
		pFont defaultFont;
		int alignment; //which side the text is aligned to (LEFT, RIGHT or CENTER)
		float wrapLimit; //what the limit of the text wrapping is

		Container<Font> * fonts; //the containers
		Container<Color> * colors;

		/**
		 * @param text A formatted text which will be split into lines.
		 * @brief Parses the passed text into lines by searching for '\n' characters.
		 **/
		void createLines(const string & text);

		/**
		 * @param font The current font. Used to determine the width of the lines of text.
		 * @param limit The size limit for the auto-linebreak.
		 * @param text A formatted text which will be split into lines.
		 * @brief Parses the passed text into lines by checking if the width of the text is too long and
		 *        searching for '\n' characters.
		 **/
		void createLines(Font * font, float limit, const string & text);

		/**
		 * @brief Outputs the text by calling the Font class.
		 **/
		void printText(Font * font, AbstractColor * color);

	public:
		static const int LOVE_ALIGN_LEFT = 1;
		static const int LOVE_ALIGN_RIGHT = 2;
		static const int LOVE_ALIGN_CENTER = 3;
		static const int LOVE_ALIGN_TOP = 4;
		static const int LOVE_ALIGN_BOTTOM = 5;

		/**
		 * @brief The default constructor.
		 **/
		Text::Text(Container<Font> * fonts, Container<Color> * colors);

		/**
		 * @brief De-CONSTRUCTOR. Fear it.
		 **/
		~Text();

		/**
		 * @param font The desired font, in a pFont object.
		 * @param color The desired color, in a pColor object.
		 * @param text An un-formatted text which will be outputted.
		 * @brief Formats the text, splits it into lines and then outputs it to the screen.
		 **/
		void printf(Font * font, AbstractColor * color, const char * text, ...);
		void printf(Font * font, const char * text, ...);
		void printf(AbstractColor * color, const char * text, ...);
		void printf(const char * text, ...);

		/**
		 * @param text Text to be outputted.
		 * @param font The desired font.
		 * @param color The desired color.
		 * @brief A quicker alternative to printf, has three other variations:
		 *		  print(font, text)
		 *	      print(color,text)
		 *        print(text)
		 **/
		void print(Font * font, AbstractColor * color, const string & text);
		void print(Font * font, AbstractColor * color, const char * text);
		void print(Font * font, const string & text);
		void print(Font * font, const char * text);
		void print(AbstractColor * color, const string & text);
		void print(AbstractColor * color, const char * text);
		void print(const string & text);
		void print(const char * text);

		/**
		 * @param x The x-coordinate the text should be outputted at.
		 * @param y The y-coordinate the text should be outputted at.
		 * @param text Text to be outputted.
		 * @brief The only function which takes the coordinates where the text will be
		 *		  outputted and is the one used in LUA.
		 **/
		void print(float x, float y, const string & text);
		void print(float x, float y, const char * text);

		// Sneaking in another method here .. (uses color/font directly) - rued
		void print(float x, float y, const char * text, Font * font, AbstractColor * color);

		void align(int alignment);
		void align(const char * alignment);
		void setLimit(float size);
		void setFont(Font * font);
		void setFont(const char * key);
		void setColor(AbstractColor * color);
		void setColor(const char * key);

		/**
		 * @return The height.
		 * @brief Returns the height of the current.
		 **/
		float getLineHeight();

		/**
		 * @return The width of the line of text.
		 * @param text A line of text.
		 * @brief Returns the width of the line of text.
		 **/
		float getLineWidth(const char * text);

		/**
		 * @brief Loads the default font (Arial) and color (0x000000).
		 **/
		int load();

		/**
		 * @brief Unloads the default font.
		 */
		void unload();
	};

	typedef boost::shared_ptr<Text> pText;
}

#endif
