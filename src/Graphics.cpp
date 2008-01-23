#include "Graphics.h"

// LOVE
#include "using_filesystem.h"

namespace love
{
	
	Graphics::Graphics()
	{
		background.reset<Color>(new Color(0, 0, 0, 255));
		color.reset<Color>(new Color(255, 255, 255, 255));
	}

	Graphics::~Graphics()
	{
	}

	int Graphics::getWidth() const
	{
		return width;
	}

	int Graphics::getHeight() const
	{
		return height;
	}

	void Graphics::setBackgroundColor(pColor color)
	{
		this->background = color;
	}

	void Graphics::setBackgroundColor(int r, int g, int b)
	{
		this->background.reset<Color>(new Color(r, g, b, 255));
	}

	void Graphics::setColor(pColor color)
	{
		this->color = color;
	}

	void Graphics::setColor(int r, int g, int b, int a)
	{
		this->color.reset<Color>(new Color(r, g, b, a));
	}

	void Graphics::setFont(pFont font)
	{
		this->font = font;
	}
	
	pFont Graphics::getCurrentFont() const
	{
		return font;
	}
	
	pColor Graphics::getCurrentBackgroundColor() const
	{
		return background;
	}
	
	pColor Graphics::getCurrentColor() const
	{
		return color;
	}

	pImage Graphics::getImage(const std::string & filename) const
	{
		pFile file = filesystem->getBaseFile(filename);
		return getImage(file);
	}

	pFont Graphics::getFont(const std::string & filename, int size) const
	{
		pFile file = filesystem->getBaseFile(filename);
		return getFont(file, size);
	}
	
	pFont Graphics::getImageFont(const std::string & filename, const std::string & glyphs) const
	{
		pFile file = filesystem->getBaseFile(filename);
		return getImageFont(file, glyphs);
	}

	void Graphics::draw(const char * str, float x, float y) const
	{
		apply(color); // Set current color.

		if(font != 0)
		{
			std::string text(str);

			if(text.find("\n") == std::string::npos)
				font->print(text, x, y);
			else
			{
				int lines = 0;
				text = "";
				
				for(unsigned int i = 0; i < std::strlen(str); i++)
				{
					if(str[i] == '\n')
					{
						font->print(text, x, y + (lines * font->getHeight() * 1.25));
						text = "";
						lines++;
					}
					else
						text += str[i];
				}
				
				if(text != "") // Print the last text (if applicable).
					font->print(text, x, y + (lines * font->getHeight() * 1.25));
			}
		}
		
		apply(pColor(new Color(255,255,255,255))); // to clear the set color
	}
	
	void Graphics::draw(const char * str, float x, float y, int wrap, int align) const
	{
		apply(color); // Set current color.

		if(font != 0)
		{
			std::string text = "";
			float width = 0;
			float lines = 0;
			
			for(unsigned int i = 0; i < std::strlen(str); i++)
			{
				if(str[i] == '\n')
				{
					switch(align)
					{
						case LOVE_ALIGN_LEFT:
							font->print(text, x, y + (lines * font->getHeight() * 1.25));
							break;
							
						case LOVE_ALIGN_RIGHT:
							font->print(text, (x + (wrap - font->getWidth(text))), y + (lines * font->getHeight() * 1.25));
							break;
							
						case LOVE_ALIGN_CENTER:
							font->print(text, (x + ((wrap - font->getWidth(text)) / 2)), y + (lines * font->getHeight() * 1.25));
							break;
							
						default: // A copy of the left align code. Kept separate in case an error message is wanted.
							font->print(text, x, y + (lines * font->getHeight()));
							break;
					}	
					text = "";
					lines++;
				}
				else
				{
					width += font->getWidth(str[i]);
					
					if(width > wrap && text.find(" ") != std::string::npos) // If there doesn't exist a space, then ignore the wrap limit.
					{						
						// Seek back to the nearest space and print that.
						unsigned int space = (unsigned int)text.find_last_of(' ');
						std::string temp = text.substr(0, space);
						
						switch(align)
						{
							case LOVE_ALIGN_LEFT:
								font->print(temp, x, y + (lines * font->getHeight() * 1.25));
								break;
							
							case LOVE_ALIGN_RIGHT:
								font->print(temp, (x + (wrap - font->getWidth(temp))), y + (lines * font->getHeight() * 1.25));
								break;
							
							case LOVE_ALIGN_CENTER:
								font->print(temp, (x + ((wrap - font->getWidth(temp)) / 2)), y + (lines * font->getHeight() * 1.25));
								break;
							
							default: // A copy of the left align code. Kept separate in case an error message is wanted.
								font->print(temp, x, y + (lines * font->getHeight()));
								break;
						}	
						
						text = text.substr(space + 1);
						width = font->getWidth(text);
						lines++;
					}
					
					text += str[i];
				}
			} // for

			if(text != "") // Print the last text (if applicable).
			{
				switch(align)
				{
					case LOVE_ALIGN_LEFT:
						font->print(text, x, y + (lines * font->getHeight() * 1.25));
						break;
							
					case LOVE_ALIGN_RIGHT:
						font->print(text, (x + (wrap - font->getWidth(text))), y + (lines * font->getHeight() * 1.25));
						break;
							
					case LOVE_ALIGN_CENTER:
						font->print(text, (x + ((wrap - font->getWidth(text)) / 2)), y + (lines * font->getHeight() * 1.25));
						break;
							
					default: // A copy of the left align code. Kept separate in case an error message is wanted.
						font->print(text, x, y + (lines * font->getHeight()));
						break;
				}	
			}
		}
		
		apply(pColor(new Color(255,255,255,255))); // to clear the set color
	}

} // love
