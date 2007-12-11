#include "Text.h"

#include <cstdio>
#include <cstdarg>
#include "love.h"
#include "Core.h"
#include "AbstractFileSystem.h"

using std::vsprintf;

namespace love
{
	void Text::createLines(const string & text)
	{
		string temp;
		lines.clear();

		for(int i = 0; i != MAX_SIZE && text[i] != '\0'; i++)
		{
			if(text[i] == '\n')
			{
				lines.push_back(temp);
				temp = "";
			}
			else
			{
				temp += text[i];
			}
		}
		//takes the last one and pushes it
		lines.push_back(temp);
	}

	void Text::createLines(AbstractFont * font, float limit, const string & text)
	{
		if(font == 0) font = defaultFont.get();

		if(limit <= 0)
		{
			createLines(text);
			return;
		}

		vector<string> words;
		vector<float> sizes;
		float size = 0;
		string temp;
		lines.clear();
		words.clear();
		sizes.clear();

		for(int i = 0; i != MAX_SIZE && text[i] != '\0'; i++)
		{
			if(text[i] == '\n')
			{
				words.push_back(temp);
				sizes.push_back(size);
				words.push_back("\n");
				sizes.push_back(0.0f);
				size = 0;
				temp = "";
			}
			else if(text[i] == ' ')
			{
				temp += text[i];
				size += font->widths[(int)' '];
				words.push_back(temp);
				sizes.push_back(size);
				size = 0;
				temp = "";
			}
			else
			{
				temp += text[i];
				size += font->widths[(int)text[i]];
			}
		}
		//takes the last one and pushes it
		words.push_back(temp);
		sizes.push_back(size);

		temp = "";
		size = 0;
		for(int i = 0; i != (int)words.size(); i++)
		{
			if(words.at(i) == "\n")
			{
				lines.push_back(temp);
				size = 0;
				temp = "";
			}
			else
			{
				size += sizes.at(i);
				
				if(size > limit && size != sizes.at(i))
				{
					lines.push_back(temp);
					size = sizes.at(i);
					temp = words.at(i);
				}
				else
					temp += words.at(i);
			}
		}
		//push the last one
		lines.push_back(temp);
	}

	void Text::printText(AbstractFont * font, AbstractColor * color)
	{
		if(font == 0) font = defaultFont.get();
		if(color == 0) color = defaultColor.get();

		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());

		int length = 0;
		// (unused) int lineCount = 0;

		float h = font->getLineHeight();//font->size / 0.63f; //we make the height about 1.5* that of

		/*for(int i = 0; i != lines.size(); i++)
		{
			glTranslatef(0, -h * i, 0);
			font->print(lines[i].c_str());
		}*/

		for(int i = 0; i != (int)lines.size(); i++)
		{
			glPushMatrix();
			length = 0;
			for(int j = 0; j != (int)lines[i].length(); j++)
				length += font->widths[(int)lines[i].c_str()[j]];

			if(length % 2 != 0) //removes a strange error
				length++;

			switch(alignment)
			{
			case 1: //LEFT
				glTranslatef(0.0f, h * i, 0.0f);
				//for(int j = 0; j != lines[i].length(); j++)
					font->print(lines[i]);
				break;
			case 2: //RIGHT
				glTranslatef(-(float)length, h * i, 0.0f);
				//for(int j = 0; j != lines[i].length(); j++)
					font->print(lines[i]);
				break;
			case 3: //CENTER
				glTranslatef(-(length / 2.0f), h * i, 0.0f);
				//for(int j = 0; j != lines[i].length(); j++)
					font->print(lines[i]);
				break;
			}
			glPopMatrix();
		}

		//glDisable(GL_TEXTURE_2D); //removed for now...
		glColor3f(1.0f,1.0f,1.0f); //so that the colouring doesn't affect any other textures
		glPopMatrix();
	}

	Text::Text() //defaults are fun
	{
		setType(LOVE_TYPE_TEXT);

		font = 0;
		color = 0;

		alignment = LOVE_ALIGN_LEFT;
		wrapLimit = 0;
	}

	Text::Text(AbstractFont * font, AbstractColor * color)
	{
		setType(LOVE_TYPE_TEXT);

		this->font = font;
		this->color = color;

		alignment = LOVE_ALIGN_LEFT;
		wrapLimit = 0;
	}

	Text::~Text()
	{
		//unload(); // don't do this... this is bad
	}

	void Text::printf(AbstractFont * font, AbstractColor * color, const char * text, ...)
	{
		if(text == 0)
			return; //pointless to continue with NO text to print

		//this is enabled and disabled every time, just in case
		glEnable(GL_TEXTURE_2D);
		//char ftext[MAX_SIZE];
		bool buffer_overrun;
		int buffer_size = 1024;
		char *ftext;
		va_list	ap;

		//for(int i = (MAX_SIZE - 1); i != 0; i--)
		//	ftext[i] = '\0'; //let's start clean

		va_start(ap, text);
			//vsprintf_s(ftext, text, ap);
			//vsprintf(ftext, text, ap);
			do
			{
				ftext = new char[buffer_size];
				buffer_overrun = vsnprintf(ftext, buffer_size, text, ap) < 0;
				if (buffer_overrun)
				{
					delete[] ftext;
					buffer_size *= 1024;
				}
			} while (buffer_overrun);
		va_end(ap);

		//turning the text into lines
		if(wrapLimit != 0)
			createLines(font, wrapLimit, ftext);
		else
			createLines(ftext);
		delete[] ftext;

		printText(font, color);
	}

	void Text::printf(const char * text, ...)
	{
		if(text == 0)
			return; //pointless to continue with NO text to print

		//this is enabled and disabled every time, just in case
		glEnable(GL_TEXTURE_2D);
		//char ftext[MAX_SIZE];
		bool buffer_overrun;
		int buffer_size = 1024;
		char *ftext;
		va_list	ap;

		//for(int i = (MAX_SIZE - 1); i != 0; i--)
		//	ftext[i] = '\0'; //let's start clean

		va_start(ap, text);
			//vsprintf(ftext, text, ap);
			do
			{
				ftext = new char[buffer_size];
				buffer_overrun = vsnprintf(ftext, buffer_size, text, ap) < 0;
				if (buffer_overrun)
				{
					delete[] ftext;
					buffer_size *= 2;
				}
			} while (buffer_overrun);
		va_end(ap);

		//turning the text into lines
		if(wrapLimit != 0)
			createLines(this->font, wrapLimit, ftext);
		else
			createLines(ftext);
		delete[] ftext;

		printText(this->font, this->color);
	}

	void Text::print(AbstractFont * font, AbstractColor * color, const string & text)
	{

		glEnable(GL_TEXTURE_2D);
		if(wrapLimit != 0)
			createLines(font, wrapLimit, text);
		else
			createLines(text);

		printText(font, color);
	}
	void Text::print(AbstractFont * font, AbstractColor * color, const char * text)
	{
		glEnable(GL_TEXTURE_2D);
		if(wrapLimit != 0)
			createLines(font, wrapLimit, string(text));
		else
			createLines(string(text));

		printText(font, color);
	}

	void Text::print(const string & text)
	{
		print(this->font, this->color, text);
	}

	void Text::print(const char * text)
	{
		print(this->font, this->color, string(text));
	}

	void Text::print(float x, float y, const string & text)
	{
		glPushMatrix();
			glTranslatef(x, y, 0.0f);
			print(this->font, this->color, text);
		glPopMatrix();
	}

	void Text::print(float x, float y, const char * text, AbstractFont * font, AbstractColor * color)
	{
		glPushMatrix();
			glTranslatef(x, y, 0.0f);
			print(font, color, string(text));
		glPopMatrix();	
	}

	void Text::align(int alignment)
	{
		// so... bitwise operators, eh?
		//makes sure the alignment is either 1, 2 or 3
		if(alignment != 0 && (alignment | 3) == 3)
			this->alignment = alignment;
	}

	void Text::setLimit(float size)
	{
		wrapLimit = size;
	}

	void Text::setFont(AbstractFont * font)
	{
		this->font = font;
	}

	void Text::setColor(AbstractColor * color)
	{
		this->color = color;
	}

	float Text::getLineHeight()
	{
		if(font == 0)
			return defaultFont->getLineHeight();
		else
			return font->getLineHeight();
	}

	float Text::getLineWidth(const char * text)
	{
		if(font == 0)
			return defaultFont->getLineWidth(text);
		else
			return font->getLineWidth(text);
	}

	int Text::load()
	{

		//const love::AbstractFileSystem & fs = love::core->getFilesystem();

		defaultFont = core->graphics->getFont("data/fonts/FreeSans.ttf", 20); 
		defaultColor.reset<Color>(new Color(0x000000));
		defaultFont->load();

		return LOVE_OK;
	}

	void Text::unload()
	{
		defaultFont->unload();
		defaultFont.reset();
		defaultColor.reset();
	}
}
