#include "NewFont.h"
#include "Image.h"
#include <vector>
#include <cmath>

using std::vector;

using love::rgba;
using love::rgb;

namespace love
{
		inline int NewFont::twoPower(int num)
		{
			int temp = 1;
			while(temp < num)
				temp *= 2;
			return temp;
		}

		void NewFont::createFont(string fontname, int size)
		{
			Image ** temp = new Image*[MAX_CHARS];
			characterTextures = new GLuint[MAX_CHARS];
			glGenTextures(MAX_CHARS, characterTextures);

			font = "data/fonts/" + fontname + ".ttf"; //fits in with the fonts folder (so far, ttf is the only supported file)
			this->size = size;

			if( FT_Init_FreeType(&library) )
				throw std::runtime_error("Fatal Error: Could not initialize FreeType");
			
			if( FT_New_Face(library, font.c_str(), 0, &face) ) //file not found error, for example
				throw std::runtime_error("Fatal Error: Could not create font face (file not found)");

			if( FT_Set_Pixel_Sizes(face, 0, size) )
				throw std::runtime_error("Fatal Error: Could not set pixel sizes");
			
			maxWidth = 0;
			maxHeight = 0;

			glEnable(GL_TEXTURE_2D); //will be disabled later, so be warned

			//finds the maxheight and maxwidths first (for the texture creation part)
			for(int i = 0; i != MAX_CHARS; i++)
			{
				if( FT_Load_Char(face, i, FT_LOAD_RENDER) )
					throw std::runtime_error("Fatal Error: Could not load character");

				temp[i] = createCharacter(i, face->glyph);

				if(temp[i]->getWidth() > maxWidth) maxWidth = temp[i]->getWidth();
				if(temp[i]->getHeight() > maxHeight) maxHeight = temp[i]->getHeight();

				widths[i] = face->glyph->bitmap_left;
				heights[i] = -face->glyph->bitmap_top;
			}

			maxWidth += 2;
			maxHeight += 2;

			int chard = (int)ceil(sqrt((double)MAX_CHARS));
			int charw = twoPower(chard * (maxWidth));
			int charh = twoPower(chard * (maxHeight));
			
			fontTexture = new Image(charw, charh, GL_LUMINANCE_ALPHA);

			for(int i = 0; i < MAX_CHARS; i++)
			{
				//-20 to compensate for the lack of the previous character (the first 12 are somehow gone...)
				int ix = (i-0) % chard;
				int iy = (int)((i-0) / chard);

				fontTexture->paste(*temp[i], ix * maxWidth, (iy * maxHeight) - temp[i]->getHeight());
			}

			fontTexture->lock();

			fontTexture->bind();

			for(int i = 0; i < MAX_CHARS; i++)
			{
				if( FT_Load_Char(face, i, FT_LOAD_RENDER) )
					throw std::runtime_error("Fatal Error: Could not load character");

				generateList((char)i, face->glyph);
			}

			glDisable(GL_TEXTURE_2D);
		}

		Image * NewFont::createCharacter(char c, FT_GlyphSlot glyph)
		{
			int gw = glyph->bitmap.width;
			int gh = glyph->bitmap.rows;

			la * data = new la[gw*gh];

			for(int j = 0; j < gh; j++)
			{
				for(int i = 0; i < gw; i++)
				{

					int di = j * gw + i;

					int bmap = glyph->bitmap.buffer[di];

					data[di].l = bmap;
					data[di].a = bmap;

				}
			}

			return new Image(gw, gh, (unsigned char *)data, GL_LUMINANCE_ALPHA);
		}

		void NewFont::generateList(char c, FT_GlyphSlot glyph)
		{
			glNewList(characterLists + (int)c, GL_COMPILE);

			//glPushMatrix();

			//glTranslatef((float)face->glyph->bitmap_left, (float)-face->glyph->bitmap_top, 0.0f);

			int x = (c - 12) % 12;
			int y = (c - 12) / 12;

			float width = (float)maxWidth;
			float height = (float)maxHeight;

			float x1 = (x * width) / fontTexture->getWidth();
			float x2 = ((x+1) * width) / fontTexture->getWidth();
			float y1 = (y * height) / fontTexture->getHeight();
			float y2 = ((y+1) * height) / fontTexture->getHeight();

			glBegin(GL_QUADS);
				glTexCoord2d(x1,y1); glVertex2f(0.0f, 0.0f);
				glTexCoord2d(x1,y2); glVertex2f(0.0f, (float)height);
				glTexCoord2d(x2,y2); glVertex2f((float)width, (float)height);
				glTexCoord2d(x2,y1); glVertex2f((float)width, 0.0f);
			glEnd();

			//glPopMatrix();

			glEndList();
		}

		/*void NewFont::createCharactercccp(char character, FT_GlyphSlot glyph)
		{
			int width, height;
			//this will fix the distorted text error
			//(wow, the beauty of checking your prog on more than one computer)
			width = twoPower(glyph->bitmap.width);
			height = twoPower(glyph->bitmap.rows);

			if(maxHeight < glyph->bitmap.rows) maxHeight = glyph->bitmap.rows;
			widths[character] = (glyph->advance.x >> 6);

			//allocate memory to the texture
			GLubyte* textureData = new GLubyte[2 * width * height];

			//NeHe's instructions on how to take the passed FT_Bitmap data and turning it
			//into useable texture data.
			for(int j = 0; j < height; j++)
			{
				for(int i = 0; i < width; i++)
				{
					textureData[2* (i + j * width)] = textureData[2 * (i + j * width) + 1] = 
						(i >= glyph->bitmap.width || j >= glyph->bitmap.rows) ?
							0 : glyph->bitmap.buffer[i + glyph->bitmap.width * j];
				}
			}
 
			//setting up some texture variables (also due to NeHe's tutorial)
			glBindTexture(GL_TEXTURE_2D, characterTextures[character]);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

			//creating the actual textures (thanks to NeHe, yet again)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, textureData );

			//now we can clean up a bit
			delete [] textureData;

			glNewList(characterLists + (int)character, GL_COMPILE);
			
			glPushMatrix();

			//glBindTexture(GL_TEXTURE_2D, characterTextures[character]);

			fontTexture->bind();

			//moving a bit to provide correct space for the glyph
			glTranslatef((float)glyph->bitmap_left, (float)-glyph->bitmap_top, 0.0f);

			//making sure that characters like 'g' and 'y' go below the line (as they should)
			/*if(top < 0)
				glTranslatef(0.0f, (float)(top + size), 0.0f);
			else if(top < height)
				glTranslatef(0.0f, (float)-(top - height), 0.0f);*/
			//messBox("character: %c\ntop: %d\nheight: %d", character, top, height);

			/*glBegin(GL_QUADS);
				glTexCoord2d(0,0); glVertex2f(0.0f, 0.0f);
				glTexCoord2d(0,1); glVertex2f(0.0f, (float)fontTexture->getHeight());
				glTexCoord2d(1,1); glVertex2f((float)fontTexture->getWidth(), (float)fontTexture->getHeight());
				glTexCoord2d(1,0); glVertex2f((float)fontTexture->getWidth(), 0.0f);
			glEnd();

			int num = (int)character - 12;

			float sizeW, sizeH;
			sizeW = (float)width / fontTexture->getWidth();
			sizeH = (float)height / fontTexture->getHeight();
			float posx = (float)((int)num % 12) - 1;
			float posy = (float)((int)num / 12) - 1;

			posx /= 12; //THIS NEEDS TO BE BETTER
			posy /= 10;

			posx += sizeW;
			posy += sizeH;
			posy -= (sizeH / 2);

			//messBox("num: %d\nposx: %f\nposy: %f", character, posx, posy);

			glBegin(GL_QUADS);
				glTexCoord2d(posx, posy);
					glVertex2f(0.0f, 0.0f);
				glTexCoord2d(posx, posy + sizeH);
					glVertex2f(0.0f, (float)height);
				glTexCoord2d(posx + sizeW, posy + sizeH);
					glVertex2f((float)width, (float)height);
				glTexCoord2d(posx + sizeW, posy);
					glVertex2f((float)width, 0.0f);
			glEnd();

			//done
			glPopMatrix();

			glTranslatef((float)(glyph->advance.x >> 6), 0, 0);

			glEndList();
		}*/

		void NewFont::messBox(const char * text, ...)
		{
			char mew[MAX_SIZE];
			va_list ap;

			va_start(ap, text);
				vsprintf_s(mew, text, ap);
			va_end(ap);

			MessageBox(0, mew, "error", MB_OK);
			//printf(mew);
		}

		NewFont::NewFont(string fontname, int size)
		{
			createFont(fontname, size);
		}

		NewFont::NewFont()
		{
			//the default font
			// I'm disabling this for now.
			//createNewFont("Verdana", 12);
		}

		NewFont::~NewFont()
		{
			delete [] characterTextures;
			glDisable(GL_TEXTURE_2D);
		}

		void NewFont::bind()
		{
			fontTexture->bind();
		}

		void NewFont::print(const char character)
		{			
			//glCallList(characterLists + (int)character);
			//the display list is being a bitch so let's do this manually

			if( FT_Load_Char(face, (int)character, FT_LOAD_RENDER) )
				throw std::runtime_error("Fatal Error: Could not load character");

			//glTranslatef((float)face->glyph->bitmap_left, -(float)face->glyph->bitmap_top, 0.0f);

			int x = (character - 12) % 12;
			int y = (character - 12) / 12;

			float width = (float)maxWidth;
			float height = (float)maxHeight;

			float x1 = (x * width) / fontTexture->getWidth();
			float x2 = ((x+1) * width) / fontTexture->getWidth();
			float y1 = (y * height) / fontTexture->getHeight();
			float y2 = ((y+1) * height) / fontTexture->getHeight();

			glBegin(GL_QUADS);
				glTexCoord2d(x1,y1); glVertex2f(0.0f, 0.0f);
				glTexCoord2d(x1,y2); glVertex2f(0.0f, (float)height);
				glTexCoord2d(x2,y2); glVertex2f((float)width, (float)height);
				glTexCoord2d(x2,y1); glVertex2f((float)width, 0.0f);
			glEnd();

			glTranslatef((float)(face->glyph->advance.x >> 6), 0.0, 0.0);

			/*glBegin(GL_QUADS);
				glTexCoord2d(0,0); glVertex2f(0.0f, 0.0f);
				glTexCoord2d(0,1); glVertex2f(0.0f, (float)fontTexture->getHeight());
				glTexCoord2d(1,1); glVertex2f((float)fontTexture->getWidth(), (float)fontTexture->getHeight());
				glTexCoord2d(1,0); glVertex2f((float)fontTexture->getWidth(), 0.0f);
			glEnd();*/
		}
}