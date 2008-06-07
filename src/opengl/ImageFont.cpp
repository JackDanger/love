#include "ImageFont.h"

#include <SDL_opengl.h>

using std::string;

namespace love_opengl
{	
	ImageFont::ImageFont(love::pFile file, std::string glyphs) : Font(file, 0)
	{
		this->glyphs = glyphs;
		image.reset<Image>(new Image(file));
	}	

	ImageFont::~ImageFont()
	{
		unload();
	}

	void ImageFont::print(string text, float x, float y) const
	{
		glPushMatrix();
		glTranslatef(x, y, 0.0f);
		GLuint OpenGLFont = list;
		glListBase(OpenGLFont);
		glCallLists((int)text.length(), GL_UNSIGNED_BYTE, text.c_str());
		glPopMatrix();
	}

	void ImageFont::print(std::string text, float x, float y, float angle, float sx, float sy) const
	{
		glPushMatrix();

		glTranslatef(x, y, 0.0f);
		glRotatef(angle, 0, 0, 1.0f);
		glScalef(sx, sy, 1.0f);

		GLuint OpenGLFont = list;
		glListBase(OpenGLFont);
		glCallLists((int)text.length(), GL_UNSIGNED_BYTE, text.c_str());

		glPopMatrix();
	}

	void ImageFont::print(char character, float x, float y) const
	{
		glPushMatrix();
		glTranslatef(x, y, 0.0f);
		GLuint OpenGLFont = list;
		glListBase(OpenGLFont);
		glCallList(list + (int)character);
		glPopMatrix();
	}

	bool ImageFont::load()
	{
		return loadVolatile();
	}

	void ImageFont::unload()
	{
		image->unload();
		unloadVolatile();
	}
	
	bool ImageFont::loadVolatile()
	{
		if(!image->read())
			return false;

		rgba * pixels = image->getData();
		
		// Reading image data begins
		size = (int)image->getHeight();
		
		for(unsigned int i = 0; i < MAX_CHARS; i++) positions[i] = -1;
		
		rgba spacer = pixels[0];
		unsigned int current = 0;
		int width = 0;
		int space = 0;

		// Finds out where the first character starts
		int firstchar = 0;
		for(int i = 0; i != (int)image->getWidth(); i++)
		{
			if(spacer.r == pixels[i].r && spacer.g == pixels[i].g && spacer.b == pixels[i].b && spacer.a == pixels[i].a)
				continue;
			else
			{
				firstchar = i;
				break;
			}
		}
		
		for(int i = firstchar; i != (int)image->getWidth(); i++)
		{			
			if(spacer.r == pixels[i].r && spacer.g == pixels[i].g && spacer.b == pixels[i].b && spacer.a == pixels[i].a)
			{
				if(width != 0) // this means we have found the end of our current character
				{
					if((unsigned int)glyphs[current] > MAX_CHARS)
						printf("Error reading image font '%s': Character '%c' is out of range.", file->getFilename().c_str(), glyphs[current]);
					else
					{
						widths[(int)glyphs[current]] = width;
						positions[(int)glyphs[current]] = i - width;
					}
					
					width = 0;
					//space++; // start counting the spacing
				}
				space++;
			}
			else
			{
				if(space != 0) // this means we have found the end of our spacing
				{
					if((unsigned int)spacing[current] > MAX_CHARS)
						printf("Error reading image font '%s': Character '%c' is out of range.", file->getFilename().c_str(), glyphs[current]);
					else
						spacing[(int)glyphs[current]] = space;

					current++;
					if(current == glyphs.size())
						i = (int)image->getWidth() - 1; // just to end it when the last character is found

					space = 0;
					//width++; // start counting the width
				}
				width++;
			}
		}
		// Reading image data ends


		// Replace spacer color with an empty pixel
		for(int i = 0; i < (int)(image->getWidth() * image->getHeight()); i++)
		{
			if(spacer.r == pixels[i].r && spacer.g == pixels[i].g && spacer.b == pixels[i].b && spacer.a == pixels[i].a)
			{
				pixels[i].r = 0;
				pixels[i].g = 0;
				pixels[i].b = 0;
				pixels[i].a = 0;
			}
		}

		// Pad and optimize
		image->pad(1);
		image->optimize();
		
		// Send to hardware
		if(!image->lock())
		{
			image->free();
			return false;
		}

		image->free();

		// Create display lists
		list = glGenLists(MAX_CHARS);

		for(unsigned int i = 0; i < MAX_CHARS; i++)
		{
			glNewList(list + i, GL_COMPILE);

			if(positions[i] != -1)
			{
				image->draws((float)positions[i] + 1, 1, (float)widths[i], (float)size+1);
				glTranslatef((float)widths[i] + ((float)spacing[i] * mSpacing), 0, 0);
			}
			else
				glTranslatef((float)widths[(int)' '], 0, 0); // empty character are replaced with a whitespace

			glEndList();
		}

		return true;
	}

	void ImageFont::unloadVolatile()
	{
		glDeleteLists(list, MAX_CHARS);
	}

	inline int ImageFont::next_p2(int num)
	{
		int powered = 2;
		while(powered < num) powered <<= 1;
		return powered;
	}
}
