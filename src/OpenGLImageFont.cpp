#include "OpenGLImageFont.h"
#include "Core.h"
#include "love.h"
#include "AbstractImageDevice.h"

namespace love
{
	void OpenGLImageFont::renderCharacter(char character)
	{
		// To Mike: g++ warns about this always being false. (MAX_CHARS = 256, 
		// and since character is a char, it can't go higher than 255. 
		// int c, the casting, etc is just circumvent this.
		//
		// FYI, g++ also complains about using char as an array index. Thus
		// the constant (int)-ing.

		unsigned int c = (int)character;

		if(c > MAX_CHARS || widths[(int)character] == -1)
			return;
		charImage->render((float)coordinates[c], 0.0f, (float)widths[c], (float)size);
	}

	OpenGLImageFont::OpenGLImageFont(pAbstractFile file, const string & glyphs) : AbstractFont(file, 0)
	{
		this->glyphs = glyphs;
		for(unsigned int i = 0; i < MAX_CHARS; i++) coordinates[i] = -1;
	}

	OpenGLImageFont::~OpenGLImageFont()
	{
		//file = 0;
		unload();
	}

	void OpenGLImageFont::print(string text, float x, float y)
	{
		glPushMatrix();
		//glColor4ub(255,255,255,255); // clearing colors shouldn't be automatic
		glTranslatef(x, y, 0.0f);
		for(unsigned int i = 0; i < text.length(); i++)
		{
			renderCharacter(text[i]);
			glTranslatef( (float)((widths[(int)text[i]] != -1) ? widths[(int)text[i]] : 0), 0.0f, 0.0f );
		}
		glPopMatrix();
	}

	void OpenGLImageFont::print(char character, float x, float y)
	{
		glPushMatrix();
		//glColor4ub(255,255,255,255); // clearing colors shouldn't be automatic
		glTranslatef(x, y, 0.0f);
		renderCharacter(character);
		glPopMatrix();
	}

	float OpenGLImageFont::getLineHeight()
	{
		return (float)size;
	}

	float OpenGLImageFont::getLineWidth(const char * line)
	{
		float temp = 0;
		for(unsigned int i = 0; i < strlen(line); i++)
			temp += widths[(int)line[i]];
		return temp;
	}

	int OpenGLImageFont::load()
	{
		if(glyphs.length() > MAX_CHARS)
		{
			core->error("OpenGLImageFont: List of glyphs is too long. MAX_CHARS=%d", MAX_CHARS);
			return LOVE_ERROR;
		}

		if(!file->load())
			return LOVE_ERROR;

		// Generate DevIL image.
		ilGenImages(1, &image);

		// Bind the image.
		ilBindImage(image);

		// Try to load the image.
		ILboolean success = ilLoadL(IL_TYPE_UNKNOWN, (void*)file->getData(), file->getSize());

		// Check for errors
		if(!success)
			printf((const char *)iluErrorString(ilGetError()));

		// Get the data
		this->width	 = (float)ilGetInteger(IL_IMAGE_WIDTH);
		this->height = (float)ilGetInteger(IL_IMAGE_HEIGHT);
		this->actualWidth = width;
		this->actualHeight = height;
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		rgba * s = (rgba *)ilGetData();

		// Get the spacer color
		Color spacer(s[0].r, s[0].g, s[0].b, s[0].a);

		const char * glyphlist = glyphs.c_str();
		unsigned int currentChar = 0; // the current character
		int charPos = 0; // the position of the current char
		int charWidth = -1; // the width of the current char

		for(int x = 0; x < this->width; x++)
		{
			Color current(s[x].r, s[x].g, s[x].b, s[x].a);
			if(current == spacer)
			{
				if(charWidth == -1) continue; // we're not reading a character, so we can just continue
				
				int temp = (int)glyphlist[currentChar];
				if(temp < 0 || temp > (int)MAX_CHARS)
				{
					core->printf("OpenGLImageFont: Character '%c'(%d) out of scope.", (char)temp, temp);
				}
				else
				{
					coordinates[temp] = charPos;
					widths[temp] = charWidth;
				}
				charPos = 0;
				charWidth = -1; // we're not reading a char anymore
				currentChar++;
				if(currentChar == strlen(glyphlist)) break;
			}
			else
			{
				if(charWidth != -1) // we're reading a char, so let's continue doing that
				{
					charWidth++;
					continue;
				}

				charPos = x;
				charWidth = 0;
			}
		}
		if(charWidth != -1 && currentChar != strlen(glyphlist)) //we have one char left
		{
			coordinates[(int)glyphlist[currentChar]] = charPos;
			widths[(int)glyphlist[currentChar]] = charWidth;
		}

		// Set the height of the font
		this->size = (int)height;

		// left here if we ever use a grid format
		/* for(int y = 0; y < this->height; y++)
			{
			for(int x = 0; x< this->width; x++)
			{
				int si = (int)(y * this->width + x);
				printf("%dx%d: %c,%c,%c,%c", x, y, s[si].r, s[si].g, s[si].b, s[si].a);
			}
		} */

		// Delete DevIL-data (no longer needed)
		ilDeleteImages(1, &image);

		file->unload();

		// Now that we have our coordinates we can load the actual image that we will use
		
		const AbstractGraphics & g = core->getGraphics();

		charImage = g.getImage(file);
		charImage->load();
		

		return LOVE_OK;
	}

	void OpenGLImageFont::unload()
	{
	}
}
