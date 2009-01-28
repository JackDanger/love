/**
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Michael Enger
* @date 2007-10-03
**/

#include "Font.h"

namespace love
{
namespace graphics
{
namespace opengl
{
	Font::Font(love::filesystem::File * file, int size) : size(size), lineHeight(1), mSpacing(1)
	{
		this->file = file;
		file->retain();
		for(unsigned int i = 0; i < MAX_CHARS; i++)
		{
			widths[i] = 0;
			spacing[i] = 0;
		}
	}

	Font::~Font()
	{
		file->release();
	}

	float Font::getHeight() const
	{
		return (float)size;
	}
	
	float Font::getWidth(const std::string & line) const
	{
		if(line.size() == 0) return 0;
		float temp = 0;

		for(unsigned int i = 0; i < line.size() - 1; i++)
		{
			temp += widths[(int)line[i]] + (spacing[(int)line[i]] * mSpacing);
		}
		temp += widths[(int)line[line.size() - 1]]; // the last character's spacing isn't counted

		return temp;
	}

	float Font::getWidth(const char * line) const
	{
		return this->getWidth(std::string(line));
	}
	
	float Font::getWidth(const char character) const
	{
		return (float)widths[(int)character];
	}

	void Font::setLineHeight(float height)
	{
		this->lineHeight = height;
	}

	float Font::getLineHeight() const
	{
		return lineHeight;
	}

	void Font::setSpacing(float amount)
	{
		mSpacing = amount;
	}

	float Font::getSpacing() const
	{
		return mSpacing;
	}

} // opengl
} // graphics
} // love
