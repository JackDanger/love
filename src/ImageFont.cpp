#include "ImageFont.h"
#include "Core.h"
#include "love.h"

namespace love
{
	void ImageFont::renderChar(char character)
	{
		if(character > MAX_CHARS || width[character] == -1)
			return;
		image->render((float)(width[character] % columns) * charwidth, floor((float)(width[character] / columns)) * size, (float)charwidth, (float)size);
	}

	ImageFont::ImageFont(pAbstractImage image, int width, int height, char * charlist) : AbstractFont(0, height)
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
			core->printf("ERROR: Unable to create Imagefont!");
			return LOVE_ERROR;
		}

		for(int i = 0; i < MAX_CHARS; i++)
			width[i] = -1;

		for(unsigned int i = 0; i < strlen(charlist); i++)
		{
			if(charlist[i] > 0 && charlist[i] < MAX_CHARS)
				width[charlist[i]] = i;
		}

		columns = (int)(image->getWidth() / charwidth);

		return LOVE_OK;
	}

	void ImageFont::unload()
	{
	}
}