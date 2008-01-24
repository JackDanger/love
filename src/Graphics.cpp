#include "Graphics.h"

// LOVE
#include "using_filesystem.h"
#include "using_display.h"
#include "using_output.h"

namespace love
{
	
	Graphics::Graphics()
	{
	}

	Graphics::~Graphics()
	{
	}

	void Graphics::push()
	{
		graphics_state s;
		states.push_back(s);
	}

	void Graphics::pop()
	{
		if(states.empty())
		{
			error("Tried to pop from an empty states stack.");
			return;
		}

		states.pop_back();
	}

	int Graphics::getWidth() const
	{
		return display->getWidth();
	}

	int Graphics::getHeight() const
	{
		return display->getHeight();
	}

	void Graphics::setBackgroundColor(pColor color)
	{
		states.back().background = color;
	}

	void Graphics::setBackgroundColor(int r, int g, int b)
	{
		states.back().background.reset<Color>(new Color(r, g, b, 255));
	}

	void Graphics::setColor(pColor color)
	{
		states.back().color = color;
	}

	void Graphics::setColor(int r, int g, int b, int a)
	{
		states.back().color.reset<Color>(new Color(r, g, b, a));
	}

	void Graphics::setFont(pFont font)
	{
		states.back().font = font;
	}
	
	pFont Graphics::getFont() const
	{
		return states.back().font;
	}
	
	pColor Graphics::getBackgroundColor() const
	{
		return states.back().background;
	}
	
	pColor Graphics::getColor() const
	{
		return states.back().color;
	}

	pImage Graphics::newImage(const std::string & filename) const
	{
		pFile file = filesystem->newBaseFile(filename);
		return newImage(file);
	}

	pFont Graphics::newFont(const std::string & filename, int size) const
	{
		pFile file = filesystem->newBaseFile(filename);
		return newFont(file, size);
	}
	
	pFont Graphics::newImageFont(const std::string & filename, const std::string & glyphs) const
	{
		pFile file = filesystem->newBaseFile(filename);
		return newImageFont(file, glyphs);
	}

	void Graphics::draw(const char * str, float x, float y) const
	{
		apply(states.back().color); // Set current color.

		const pFont & font = states.back().font;

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
		apply(states.back().color); // Set current color.

		const pFont & font = states.back().font;

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
