#include "Font.h"
#include "Core.h"
#include "love.h"
#include "AbstractFile.h"

namespace love
{
	inline int Font::next_p2(int num)
	{
		int powered = 2;
		while(powered < num) powered <<= 1;
		return powered;
	}

	inline void Font::pushScreenCoordinateMatrix()
	{
		glPushAttrib(GL_TRANSFORM_BIT);
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(viewport[0],viewport[2],viewport[1],viewport[3]);
		glPopAttrib();
	}

	inline void Font::popProjectionMatrix()
	{
		glPushAttrib(GL_TRANSFORM_BIT);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glPopAttrib();
	}

	void Font::createFont(const char * fontpath, unsigned int size)
	{

	}

	void Font::createList(FT_Face face, unsigned short character)
	{
		if( FT_Load_Glyph(face, FT_Get_Char_Index(face, character), FT_LOAD_DEFAULT) )
			core->error("Font Loading Error: FT_Load_Glyph failed.");
			//throw std::runtime_error("FT_Load_Glyph failed");

		FT_Glyph glyph;
		if( FT_Get_Glyph(face->glyph, &glyph) )
			core->error("Font Loading Error: FT_Get_Glyph failed.");
			//throw std::runtime_error("FT_Get_Glyph failed");

		FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, 0, 1);
		FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

		FT_Bitmap& bitmap = bitmap_glyph->bitmap; //just to make things easier

		width[character] = face->glyph->advance.x >> 6;
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

		float	x=(float)bitmap.width / (float)w,
				y=(float)bitmap.rows / (float)h;

		glBegin(GL_QUADS);
			glTexCoord2d(0, 0); glVertex2f(0, 0);
			glTexCoord2d(0, y); glVertex2f(0, (float)bitmap.rows);
			glTexCoord2d(x, y); glVertex2f((float)bitmap.width, (float)bitmap.rows);
			glTexCoord2d(x, 0); glVertex2f((float)bitmap.width, 0);
		glEnd();
		glPopMatrix();
		glTranslatef((float)(face->glyph->advance.x >> 6) ,0,0);

		glEndList();

		FT_Done_Glyph(glyph);
	}

	Font::Font(AbstractFile * file, int size) : AbstractFont(file, size)
	{
	}	

	Font::~Font()
	{
		unload();
	}

	void Font::print(const char * text, float x, float y)
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);

		glTranslatef(x, y, 0.0f);
		GLuint font = list;
		glListBase(font);
		glCallLists((int)strlen(text), GL_UNSIGNED_BYTE, text);

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}

	void Font::print(string text, float x, float y)
	{
		print(text.c_str(), x, y);
	}

	void Font::print(char character, float x, float y)
	{
		glPushMatrix();
		glTranslatef(x, y, 0.0f);
		GLuint font = list;
		glListBase(font);
		glCallList(character);
		glPopMatrix();
	}

	float Font::getLineHeight()
	{
		return ((float)size) * 1.5f;
	}

	float Font::getLineWidth(const char * line)
	{
		float temp = 0;

		for(unsigned int i = 0; i < strlen(line); i++)
		{
			temp += width[(int)line[i]];
		}

		return temp;
	}

	int Font::load()
	{

		// Load file
		file->load();


		textures = new GLuint[MAX_CHARS];
		for(int i = 0; i != MAX_CHARS; i++) width[i] = 0;

		FT_Library library;
		if( FT_Init_FreeType(&library) )
			core->error("Font Loading Error: FT_Init_FreeType failed.");
			//throw std::runtime_error("FT_Init_FreeType failed");

		FT_Face face;
		if( FT_New_Memory_Face( library,
								(const FT_Byte *)file->getData(),    /* first byte in memory */
								file->getSize(),      /* size in bytes        */
								0,         /* face_index           */
								&face ))
			core->error("Font Loading Error: FT_New_Face failed (there is probably a problem with your font file).");
			//throw std::runtime_error("FT_New_Face failed (there is probably a problem with your font file)");

		FT_Set_Char_Size(face, size << 6, size << 6, 96, 96);

		list = glGenLists(MAX_CHARS);
		glGenTextures(MAX_CHARS, textures);
		for(unsigned short i = 0; i < MAX_CHARS; i++)
			createList(face, i);

		FT_Done_Face(face);
		FT_Done_FreeType(library); //all done

		//printf("Loading font: %s (%i px)\n", file->getFilename().c_str(), size);
		file->unload();

		return LOVE_OK;
	}

	void Font::unload()
	{
		//printf("Unoading font: %s (%i px)\n", file->getFilename().c_str(), size);
		glDeleteLists(list, MAX_CHARS);
		glDeleteTextures(MAX_CHARS, textures);
	}

}
