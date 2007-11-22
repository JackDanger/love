#include "ImageFont.h"
#include "Core.h"
#include "love.h"

namespace love
{
	void ImageFont::renderChar(char character)
	{
		// To Mike: g++ warns about this always being false. (MAX_CHARS = 256, 
		// and since character is a char, it can't go higher than 255. 
		// int c, the casting, etc is just circumvent this.
		//
		// FYI, g++ also complains about using char as an array index. Thus
		// the constant (int)-ing.

		int c = (int) character;

		if(c > MAX_CHARS || width[(int)character] == -1)
			return;
		image->render((float)(width[(int)character] % columns) * charwidth, floor((float)(width[(int)character] / columns)) * size, (float)charwidth, (float)size);
	}

	ImageFont::ImageFont(pAbstractImage image, int width, int height, const string & charlist) : AbstractFont(0, height)
	{
		this->image = image;
		this->charwidth = width;
		this->charlist = charlist;
	}

	ImageFont::~ImageFont()
	{
		unload();
	}

	void ImageFont::print(const char * text, float x, float y)
	{
		glPushMatrix();
		glTranslatef(x,y - getLineHeight(),0.0f);
		//glColor4ub(255,255,255,255); //might want to remove this?
		for(unsigned int i = 0; i < strlen(text); i++)
		{
			renderChar(text[i]);
			glTranslatef((float)charwidth, 0.0f,0.0f);
		}
		glPopMatrix();
	}

	void ImageFont::print(string text, float x, float y)
	{
		print(text.c_str(), x, y);
	}

	void ImageFont::print(char character, float x, float y)
	{
		glPushMatrix();
		glTranslatef(x,y,0.0f);
		//glColor4ub(255,255,255,255); //might want to remove this?
		renderChar(character);
		glPopMatrix();
	}

	float ImageFont::getLineHeight()
	{
		return (float)size;
	}

	float ImageFont::getLineWidth(const char * line)
	{
		return (float)(strlen(line) * charwidth);
	}

	int ImageFont::load()
	{
		//image->load(); //we assume that it has been loaded already

		if(width <= 0 || size <= 0)
		{
			core->error("ImageFont: Unable to create font!");
			return LOVE_ERROR;
		}

		for(int i = 0; i < MAX_CHARS; i++)
			width[i] = -1;

		for(unsigned int i = 0; i < charlist.length(); i++)
		{
			// To Mike: ... same as the comment in renderChar.
			
			int c = (int) charlist[i];
			
			if(c > 0 && c < MAX_CHARS)
				width[(int)charlist[i]] = i;
		}

		columns = (int)(image->getWidth() / charwidth);

		return LOVE_OK;
	}

	void ImageFont::unload()
	{
	}
}
