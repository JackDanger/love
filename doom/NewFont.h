#ifndef AMF_NEWFONT_H
#define AMF_NEWFONT_H

#define NUM_CHARACTERS 96

#include <string>
#include <vector>

#include "love_gl.h"
#include "Loadable.h"
#include "Image.h"

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace std;

namespace love
{
		using std::vector;
		using std::string;

		/**
		* @class Font
		* @version 1.0
		* @since 1.0
		* @author Michael Enger
		* @date 2006-05-14
		* @brief A class to handle text output. Uses the library FreeType2 (available here: http://www.freetype.org/) and takes use of both their local documentation and NeHe's experience.
		**/
		class NewFont
		{
		private:
			//define ^^ 
			static const int MAX_SIZE = 512; //max size for every line of text
			static const int MAX_CHARS = 128; //max characters to get from the font file
			
			FT_Library library;
			FT_Face face;
			GLuint *characterTextures;
			GLuint characterLists;
			string font;
			int size;
			Image * fontTexture;

			/**
			 * @param num The width or height of the texture.
			 * @brief Gets the first power of two number which is >= num. Used when OpenGL2 is not detected (because then textured sized to a non ^2 number fails to show).
			 **/
			inline int twoPower(int num);

			/**
			 * @param fontname The name of the font which will be used in the style: "fonts/" fontname ".ttf"
			 * @param size The size of the font.
			 * @brief This is where the font gets created. The TrueType file read, the glyphs extracted and the texture put together.
			 **/
			void createFont(string fontname, int size);

			/**
			 * @param c The character to be texture'd.
			 * @param glyph A FT_GlyphSlot object where the Bitmap texture will be read from.
			 * @brief Makes a texture of the glyph for the representative character and returns the completed texture (Image).
			 **/
			Image * createCharacter(char c, FT_GlyphSlot glyph);

			/**
			 * @param c The character to be display list'd
			 * @param glyph A FT_GlyphSlot object where certain information is stored
			 * @brief Creates a display list for that specific character.
			 **/
			void generateList(char c, FT_GlyphSlot glyph);

			/**
			 * @param text Formatted text ("bla bla %d bla")
			 * @brief Prints out text with variables in a message box.
			 **/
			void messBox(const char * text, ...);

		public:
			//define ^^
			static const int LEFT = 1;
			static const int RIGHT = 2;
			static const int CENTER = 3;

			int widths[MAX_CHARS];
			int heights[MAX_CHARS];
			int maxHeight, maxWidth;

			/**
			 * @param fontname The name of the font (which should be a .ttf file in a the .\fonts folder.
			 * @param size What size (in pixels) the selected font should be.
			 * @brief The main constructor which initializes the font for use.
			 **/
			NewFont(string fontname, int size);

			/**
			 * @brief Default constructor which isn't really supposed to be used but (just in case it is ever called) it just calls createFont("Verdana", 12) as a default font.
			 **/
			NewFont();

			/**
			 * @brief Cleans up the object, deleting anything/everything.
			 **/
			~NewFont();

			/**
			 * @brief Just binds the fontTexture.
			 **/
			void bind();

			/**
			 * @param character A character.
			 * @brief Reads the display list for the appropriate character.
			 **/
			void print(const char character);
		};

		typedef boost::shared_ptr<NewFont> pNewFont;

}//love

#endif
