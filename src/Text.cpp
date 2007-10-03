#include "Text.h"

#include "Container.h"

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

	void Text::createLines(Font * font, float limit, const string & text)
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
					size += font->width[(int)' '];
					words.push_back(temp);
					sizes.push_back(size);
					size = 0;
					temp = "";
				}
				else
				{
					temp += text[i];
					size += font->width[(int)text[i]];
				}
			}
			//takes the last one and pushes it
			words.push_back(temp);
			sizes.push_back(size);

			temp = "";
			size = 0;
			for(int i = 0; i != words.size(); i++)
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

	void Text::printText(Font * font, AbstractColor * color)
	{
		if(font == 0) font = defaultFont.get();
		if(color == 0) color = defaultColor.get();

		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());

		int length = 0;
		int lineCount = 0;

		float h = font->getLineHeight();//font->size / 0.63f; //we make the height about 1.5* that of

		/*for(int i = 0; i != lines.size(); i++)
		{
			glTranslatef(0, -h * i, 0);
			font->print(lines[i].c_str());
		}*/

		for(int i = 0; i != lines.size(); i++)
		{
			glPushMatrix();
			length = 0;
			for(int j = 0; j != lines[i].length(); j++)
				length += font->width[lines[i].c_str()[j]];

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

	Text::Text(Container<Font> * fonts, Container<Color> * colors) //defaults are fun
	{
		setType(LOVE_TYPE_TEXT);

		this->fonts = fonts;
		this->colors = colors;

		font = 0;
		color = 0;

		alignment = LOVE_ALIGN_LEFT;
		wrapLimit = 0;
	}

	Text::~Text()
	{}

	void Text::printf(Font * font, AbstractColor * color, const char * text, ...)
	{
		//this is enabled and disabled every time, just in case
		glEnable(GL_TEXTURE_2D);
		char ftext[MAX_SIZE];
		va_list	ap;

		if(text == 0)
			return; //pointless to continue with NO text to print

		for(int i = (MAX_SIZE - 1); i != 0; i--)
			ftext[i] = '\0'; //let's start clean

		va_start(ap, text);
			//vsprintf_s(ftext, text, ap);
			vsprintf(ftext, text, ap);
		va_end(ap);

		//turning the text into lines
		if(wrapLimit != 0)
			createLines(font, wrapLimit, ftext);
		else
			createLines(ftext);

		printText(font, color);
	}
	void Text::printf(Font * font, const char * text, ...)
	{
		//this is enabled and disabled every time, just in case
		glEnable(GL_TEXTURE_2D);
		char ftext[MAX_SIZE];
		va_list	ap;

		if(text == 0)
			return; //pointless to continue with NO text to print

		for(int i = (MAX_SIZE - 1); i != 0; i--)
			ftext[i] = '\0'; //let's start clean

		va_start(ap, text);
			//vsprintf_s(ftext, text, ap);
		vsprintf(ftext, text, ap);
		va_end(ap);

		//turning the text into lines
		if(wrapLimit != 0)
			createLines(font, wrapLimit, ftext);
		else
			createLines(ftext);

		printText(font, this->color);
	}
	void Text::printf(AbstractColor * color, const char * text, ...)
	{
		//this is enabled and disabled every time, just in case
		glEnable(GL_TEXTURE_2D);
		char ftext[MAX_SIZE];
		va_list	ap;

		if(text == 0)
			return; //pointless to continue with NO text to print

		for(int i = (MAX_SIZE - 1); i != 0; i--)
			ftext[i] = '\0'; //let's start clean

		va_start(ap, text);
			vsprintf(ftext, text, ap);
		va_end(ap);

		//turning the text into lines
		if(wrapLimit != 0)
			createLines(this->font, wrapLimit, ftext);
		else
			createLines(ftext);

		printText(this->font, color);
	}
	void Text::printf(const char * text, ...)
	{
		//this is enabled and disabled every time, just in case
		glEnable(GL_TEXTURE_2D);
		char ftext[MAX_SIZE];
		va_list	ap;

		if(text == 0)
			return; //pointless to continue with NO text to print

		for(int i = (MAX_SIZE - 1); i != 0; i--)
			ftext[i] = '\0'; //let's start clean

		va_start(ap, text);
			vsprintf(ftext, text, ap);
		va_end(ap);

		//turning the text into lines
		if(wrapLimit != 0)
			createLines(this->font, wrapLimit, ftext);
		else
			createLines(ftext);

		printText(this->font, this->color);
	}

	void Text::print(Font * font, AbstractColor * color, const string & text)
	{
		glEnable(GL_TEXTURE_2D);
		if(wrapLimit != 0)
			createLines(font, wrapLimit, text);
		else
			createLines(text);

		printText(font, color);
	}
	void Text::print(Font * font, AbstractColor * color, const char * text)
	{
		glEnable(GL_TEXTURE_2D);
		if(wrapLimit != 0)
			createLines(font, wrapLimit, string(text));
		else
			createLines(string(text));

		printText(font, color);
	}

	void Text::print(Font * font, const string & text)
	{
		print(font, this->color, text);
	}
	void Text::print(Font * font, const char * text)
	{
		print(font, this->color, string(text));
	}

	void Text::print(AbstractColor * color, const string & text)
	{
		print(this->font, color, text);
	}
	void Text::print(AbstractColor * color, const char * text)
	{
		print(this->font, color, string(text));
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
	void Text::print(float x, float y, const char * text)
	{
		glPushMatrix();
			glTranslatef(x, y, 0.0f);
			print(this->font, this->color, string(text));
		glPopMatrix();
	}

	void Text::print(float x, float y, const char * text, Font * font, AbstractColor * color)
	{
		glPushMatrix();
			glTranslatef(x, y, 0.0f);
			print(font, color, string(text));
		glPopMatrix();	
	}

	void Text::align(int alignment)
	{
		this->alignment = alignment;
	}

	void Text::align(const char * alignment)
	{
		this->alignment = 1;

		if(strcmp(alignment, "left") == 0)
			this->alignment = 1;
		else if(strcmp(alignment, "right") == 0)
			this->alignment = 2;
		else if(strcmp(alignment, "center") == 0)
			this->alignment = 3;
	}

	void Text::setLimit(float size)
	{
		wrapLimit = size;
	}

	void Text::setFont(Font * font)
	{
		this->font = font;
	}

	void Text::setFont(const char * key)
	{
		font = (*fonts)[key].get();
	}

	void Text::setColor(AbstractColor * color)
	{
		this->color = color;
	}

	void Text::setColor(const char * key)
	{
		color = (*colors)[key].get();
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

		const love::AbstractFileSystem & fs = love::core->getFilesystem();

		defaultFont.reset<Font>(new Font(fs.getBaseFile("data/fonts/FreeSans.ttf"), 20));
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
