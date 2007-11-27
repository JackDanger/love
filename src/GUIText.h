#ifndef LOVE_GUI_TEXT_H
#define LOVE_GUI_TEXT_H

#include "AbstractFont.h"
#include "Color.h"

#include "guichan/font.hpp"
#include "guichan/opengl.hpp"
#include "guichan/platform.hpp"
#include "guichan/rectangle.hpp"

#include <boost/shared_ptr.hpp>

using std::string;

namespace love
{
	class GUIText : public gcn::Font
	{
	private:
		pAbstractFont font;

	public:
		GUIText(pAbstractFont font);
       
		virtual ~GUIText();

		virtual int getWidth(unsigned char glyph) const;
        virtual int getWidth(const std::string& text) const;
		virtual int getHeight() const;
		
		virtual pAbstractFont getFont();
		virtual void setFont(AbstractFont * font);
		virtual void setFont(pAbstractFont font);

        virtual void drawString(gcn::Graphics* graphics, const std::string& text, int x, int y);
	};

	typedef boost::shared_ptr<GUIText> pGUIText;
}

#endif
