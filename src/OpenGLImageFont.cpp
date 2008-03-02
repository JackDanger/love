#include "OpenGLImageFont.h"

// LOVE
#include "using_gl.h"
#include "using_output.h"
#include "using_filesystem.h"
#include "using_graphics.h"

using std::string;

namespace love
{	
	OpenGLImageFont::OpenGLImageFont(pFile file, std::string glyphs) : Font(file, 0)
	{
		this->glyphs = glyphs;
		image = graphics->newImage(file);
	}	

	OpenGLImageFont::~OpenGLImageFont()
	{
		unload();
	}

	void OpenGLImageFont::print(string text, float x, float y) const
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		
		glTranslatef(x, y, 0.0f);
		GLuint OpenGLFont = list;
		glListBase(OpenGLFont);
		glCallLists((int)text.length(), GL_UNSIGNED_BYTE, text.c_str());

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}

	void OpenGLImageFont::print(char character, float x, float y) const
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);

		glTranslatef(x, y, 0.0f);
		GLuint OpenGLFont = list;
		glListBase(OpenGLFont);
		glCallList(list + (int)character);

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}

	bool OpenGLImageFont::load()
	{
		image->readData();
		rgba * pixels = image->getData();
		
		// Reading image data begins
		size = (int)image->getHeight();
		
		for(unsigned int i = 0; i < MAX_CHARS; i++) positions[i] = -1;
		
		rgba spacer = pixels[0];
		unsigned int current = 0;
		int width = 0;
		int space = 0;
		
		for(int i = 1; i != (int)image->getWidth(); i++)
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
		// Reading image data ends.

		
		// Create display lists
		image->toHardware();
		image->freeData();
		
		list = glGenLists(MAX_CHARS);
		
		glEnable(GL_TEXTURE_2D);

		for(unsigned int i = 0; i < MAX_CHARS; i++)
		{
			glNewList(list + i, GL_COMPILE);

			if(positions[i] != -1)
			{
				image->render((float)positions[i], 0, (float)widths[i], (float)size);
		
				glTranslatef((float)widths[i] + (float)spacing[i], 0, 0);
			}
			else
				glTranslatef((float)widths[(int)' '], 0, 0); // empty character are replaced with a whitespace

			glEndList();
		}

		return true;
	}

	void OpenGLImageFont::unload()
	{
		image->unload();
		
		glDeleteLists(list, MAX_CHARS);
	}
	
	inline int OpenGLImageFont::next_p2(int num)
	{
		int powered = 2;
		while(powered < num) powered <<= 1;
		return powered;
	}
}
