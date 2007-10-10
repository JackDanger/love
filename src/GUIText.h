#ifndef LOVE_GUI_TEXT_H
#define LOVE_GUI_TEXT_H

#include "AbstractFont.h"
#include "Color.h"


#include "guichan/font.hpp"
#include "guichan/opengl.hpp"
#include "guichan/platform.hpp"
#include "guichan/rectangle.hpp"


using std::string;

namespace love
{
	class GUIText : public gcn::Font
	{
	private:
		love::AbstractFont * font;
		AbstractColor * color;

	public:
		GUIText(love::AbstractFont * font, AbstractColor * color);
       
		virtual ~GUIText();

		virtual int getWidth(unsigned char glyph) const;

        virtual int getWidth(const std::string& text) const;

		virtual int getHeight() const;

		virtual void setColor(gcn::Color color);
		
		virtual love::AbstractFont * getFont();
		virtual void setFont(love::AbstractFont * font);
		virtual AbstractColor * getColor();
		virtual void setColor(AbstractColor * color);

        virtual void drawString(gcn::Graphics* graphics, const std::string& text, int x, int y);
	};
}

#endif