#include "OpenGLImageFont.h"

// LOVE
#include "using_gl.h"
#include "using_error.h"
#include "using_filesystem.h"
#include "using_graphics.h"

using std::string;

namespace love
{
	void OpenGLImageFont::createList(unsigned short character)
	{
		/*if( FT_Load_Glyph(face, FT_Get_Char_Index(face, character), FT_LOAD_DEFAULT) )
			error("OpenGLFont Loading Error: FT_Load_Glyph failed.");
			//throw std::runtime_error("FT_Load_Glyph failed");

		FT_Glyph glyph;
		if( FT_Get_Glyph(face->glyph, &glyph) )
			error("OpenGLFont Loading Error: FT_Get_Glyph failed.");
			//throw std::runtime_error("FT_Get_Glyph failed");

		FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, 0, 1);
		FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

		FT_Bitmap& bitmap = bitmap_glyph->bitmap; //just to make things easier

		widths[character] = face->glyph->advance.x >> 6;
		int w = next_p2(bitmap.width);
		int h = next_p2(bitmap.rows);

		GLubyte* expandedData = new GLubyte[ 2 * w * h];

		for(int j = 0; j < h; j++) for(int i = 0; i < w; i++)
		{
			expandedData[2 * (i + j * w)] = MAX_CHARS-1;
			expandedData[2 * (i + j * w) + 1] = (i >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width * j];
		}

		glBindTexture(GL_TEXTURE_2D, textures[character]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Rude adds:
		// (You're welcome, Mike.)
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expandedData);



		delete [] expandedData; //no longer needed

		glNewList(list + character, GL_COMPILE);

			glBindTexture(GL_TEXTURE_2D, textures[character]);

			glPushMatrix();

			glTranslatef((float)bitmap_glyph->left, -(float)bitmap_glyph->top, 0);
			//glTranslatef(0, (float)bitmap_glyph->top-bitmap.rows, 0);

			float x=(float)bitmap.width / (float)w, y=(float)bitmap.rows / (float)h;
			
			glBegin(GL_QUADS);
			glTexCoord2d(0, 0); glVertex2f(0, 0);
			glTexCoord2d(0, y); glVertex2f(0, (float)bitmap.rows);
			glTexCoord2d(x, y); glVertex2f((float)bitmap.width, (float)bitmap.rows);
			glTexCoord2d(x, 0); glVertex2f((float)bitmap.width, 0);
			glEnd();
			glPopMatrix();
	
			glTranslatef((float)(face->glyph->advance.x >> 6) ,0,0);
			
		glEndList();
		
		FT_Done_Glyph(glyph);*/
	}
	
	OpenGLImageFont::OpenGLImageFont(pFile file, std::string glyphs) : Font(file, 0)
	{
		this->glyphs = glyphs;
		image = graphics->getImage(file);
	}	

	OpenGLImageFont::~OpenGLImageFont()
	{
		unload();
	}

	void OpenGLImageFont::print(string text, float x, float y) const
	{
		unsigned int pos;
		
		//image->render(x, y);
		
		glPushMatrix();
		glTranslatef(x, y, 0.0f);
		
		glColor4ub(255,255,255,255); // should this be removed?
		
		for(unsigned int i = 0; i != text.size(); i++)
		{
			pos = (unsigned int)text[i];
			
			if(positions[pos] != -1)
			{
				image->render((float)positions[pos], 0, (float)widths[pos], (float)size);
				glTranslatef((float)widths[pos], 0.0f, 0.0f);
			}
			else // in case the character is not found
				glTranslatef((float)widths[(int)' '], 0.0f, 0.0f);
		}
		
		glPopMatrix();
		
		/*glPushMatrix();
		glEnable(GL_TEXTURE_2D);

		glTranslatef(ceil(x), ceil(y), 0.0f);
		GLuint OpenGLFont = list;
		glListBase(OpenGLFont);
		glCallLists((int)text.length(), GL_UNSIGNED_BYTE, text.c_str());

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();*/
	}

	void OpenGLImageFont::print(char character, float x, float y) const
	{
		unsigned int pos = (unsigned int)character;
		
		if(pos > MAX_CHARS || positions[pos] == -1) return;
		
		glPushMatrix();
		glTranslatef(x, y, 0.0f);
		
		glColor4ub(255,255,255,255); // should this be removed?
			
		image->render((float)positions[pos], 0, (float)widths[pos], (float)size);
		
		glPopMatrix();
		
		/*glPushMatrix();
		glTranslatef(x, y, 0.0f);
		GLuint OpenGLFont = list;
		glListBase(OpenGLFont);
		glCallList(character);
		glPopMatrix();*/
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
		
		for(int i = 1; i != (int)image->getWidth(); i++)
		{			
			if(spacer.r == pixels[i].r && spacer.g == pixels[i].g && spacer.b == pixels[i].b && spacer.a == pixels[i].a)
			{
				if(width != 0) //this means we have found the end of our current image
				{
					if((unsigned int)glyphs[current] > MAX_CHARS)
						printf("Error reading image font: Character '%c' is out of range.\n", glyphs[current]);
					else
					{
						widths[(int)glyphs[current]] = width;
						positions[(int)glyphs[current]] = i - width;
					}
					
					width = 0;
					current++;
					if(current == glyphs.size()) // just to end it when the last character is found
						i = (int)image->getWidth() - 1;
				}
			}
			else
				width++;
		}
		
		// Reading image data ends.

		image->toHardware();
		image->freeData();

		return true;
	}

	void OpenGLImageFont::unload()
	{
		image->unload();
	}	

}
